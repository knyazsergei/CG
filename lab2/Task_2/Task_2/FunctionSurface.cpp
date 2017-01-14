#include "stdafx.h"
#include "FunctionSurface.h"
#include <algorithm>

namespace
{
	const float DOT_SIZE = 5.f;

	glm::vec3 GetPosition(const Function2D &fn, float x, float z)
	{
		return fn(x, z);
	}

	void CalculateNormals(SVertexP3N &vertice,
		const Function2D &fn, float step,
		float u, float v)
	{
		glm::vec3 directionV1 = fn(u, v + step) - vertice.position;
		glm::vec3 directionV2 = (fn(u + step, v) - vertice.position);
		vertice.normal = glm::normalize(glm::cross(directionV1, directionV2));
	}

	/// Привязывает вершины к состоянию OpenGL,
	/// затем вызывает 'callback'.
	template <class T>
	void DoWithBindedArrays(const std::vector<SVertexP3N> &vertices, T && callback)
	{
		// Включаем режим vertex array и normal array.
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_NORMAL_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);


		// Выполняем привязку vertex array и normal array
		const size_t stride = sizeof(SVertexP3N);
		glNormalPointer(GL_FLOAT, stride, glm::value_ptr(vertices[0].normal));
		glVertexPointer(3, GL_FLOAT, stride, glm::value_ptr(vertices[0].position));
		glColorPointer(3, GL_FLOAT, stride, glm::value_ptr(vertices[0].color));
		// Выполняем внешнюю функцию.
		callback();

		glDisableClientState(GL_COLOR_ARRAY);
		// Выключаем режим vertex array и normal array.
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);
		
	}

	void CalculateTriangleStripIndicies(std::vector<uint32_t> &indicies,
		unsigned columnCount, unsigned rowCount)
	{
		indicies.clear();
		indicies.reserve((columnCount - 1) * rowCount * 2);
		// вычисляем индексы вершин.
		for (unsigned ci = 0; ci < columnCount - 1; ++ci)
		{
			if (ci % 2 == 0)
			{
				for (unsigned ri = 0; ri < rowCount; ++ri)
				{
					unsigned index = ci * rowCount + ri;
					indicies.push_back(index + rowCount);
					indicies.push_back(index);
				}
			}
			else
			{
				for (unsigned ri = rowCount - 1; ri < rowCount; --ri)
				{
					unsigned index = ci * rowCount + ri;
					indicies.push_back(index);
					indicies.push_back(index + rowCount);
				}
			}
		}
	}


	const glm::vec3 MAX_COLOR = { 1, 0, 1 };
	const glm::vec3 MIN_COLOR = { 0, 1, 0 };
	const glm::vec3 GREEN_COLOR = { 1.f, 1.f, 0.f };

	// Приводит значение от входного диапазона к диапазону [0;1]
	float NormalizeValue(float value, glm::vec2 const& range)
	{
		const float length = (std::abs(range.x - range.y));
		return std::abs(range.y - value) / length;
	}

	void ApplyColor(std::vector<SVertexP3N> &vertices, bool isColor, std::vector<glm::vec3> const & colors)
	{
		auto color = colors.front();
		for (auto & v : vertices)
		{
			if (isColor)
			{
				v.color = color;
			}
			else
			{
				v.color = GREEN_COLOR;
			}
		}		
	}
}

CSolidFunctionSurface::CSolidFunctionSurface(const Function2D &fn)
	: m_fn(fn)
{
}

void CSolidFunctionSurface::Tesselate(const glm::vec2 &rangeX, const glm::vec2 &rangeZ, float step)
{
	const unsigned columnCount = unsigned((rangeX.y - rangeX.x) / step) + 2;
	const unsigned rowCount = unsigned((rangeZ.y - rangeZ.x) / step) + 1 ;
	m_vertices.clear();
	m_vertices.reserve(columnCount * rowCount);

	// вычисляем позиции вершин.
	for (unsigned ci = 0; ci < columnCount; ++ci)
	{
		const float u = rangeX.x + step * float(ci);
		for (unsigned ri = 0; ri < rowCount; ++ri)
		{
			const float v = rangeZ.x + step * float(ri);
			auto vertice = SVertexP3N(m_fn(u, v));

			float yParam = vertice.position.y;
			m_range.y = std::min(yParam, m_range.y);
			m_range.x = std::max(yParam, m_range.x);
			CalculateNormals(vertice, m_fn, step, u, v);

			m_vertices.push_back(vertice);
		}
	}
	CalculateTriangleStripIndicies(m_indicies, columnCount, rowCount);
	CalculateColor();
}


void CSolidFunctionSurface::Draw() const
{
	auto mode = GL_FILL;
	if (m_isFrame)
	{
		mode = GL_LINE;
	}

	glPolygonMode(GL_FRONT_AND_BACK, mode);
	DoWithBindedArrays(m_vertices, [&] {
		
		glDrawElements(GL_TRIANGLE_STRIP, GLsizei(m_indicies.size()),
			GL_UNSIGNED_INT, m_indicies.data());
	});
}

void CSolidFunctionSurface::ChangeMode()
{
	m_isFrame = !m_isFrame;
}

void CSolidFunctionSurface::ChangeColorMode()
{
	m_isColor = !m_isColor;
}

void CSolidFunctionSurface::CalculateColor()
{
	for (auto & v : m_vertices)
	{
		const float normalizedY = NormalizeValue(v.position.y, m_range);
		v.color = MAX_COLOR * (1 - normalizedY) + MIN_COLOR * normalizedY;
	}
}
