#include "stdafx.h"
#include "Window.h"
#include <boost/range/algorithm/find_if.hpp>
#include <boost/range/adaptor/reversed.hpp>

namespace
{
	const glm::vec4 BLACK = { 0, 0, 0, 1 };
	const glm::vec4 WHITE = { 1, 1, 1, 1 };
	const glm::vec4 LIGHT_YELLOW_RGBA = { 1.f, 1.f, 0.5f, 1.f };
	const glm::vec4 WHITE_LIGHT = { 1, 1, 1, 1 };
	const glm::vec3 SUNLIGHT_DIRECTION = { -1.f, 0.2f, 0.7f };

	const float CAMERA_INITIAL_ROTATION = 0;
	const float CAMERA_INITIAL_DISTANCE = 5.f;

	// включает смешивание цветов
	// перед выводом полупрозрачных тел
	void enableBlending()
	{
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	// отключает смешивание цветов
	// перед выводом непрозрачных тел
	void disableBlending()
	{
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}

	void SetupOpenGLState()
	{
		// включаем механизмы трёхмерного мира.
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);


		// включаем систему освещения
		glEnable(GL_LIGHTING);

		// включаем применение цветов вершин как цвета материала.
		glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	}
}


CWindow::CWindow()
	: m_camera(CAMERA_INITIAL_ROTATION, CAMERA_INITIAL_DISTANCE)
	, m_sunlight(GL_LIGHT0)
{
	SetBackgroundColor(BLACK);
	m_rhombicuboctahedron.SetAlpha(0.7f);
	
	m_sunlight.SetDirection(SUNLIGHT_DIRECTION);
	m_sunlight.SetAmbient(0.1f * WHITE);
	m_sunlight.SetSpecular(WHITE);
}

void CWindow::OnWindowInit(const glm::ivec2 &size)
{
	(void)size;
	SetupOpenGLState();
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
	m_time += deltaSeconds;
	m_rhombicuboctahedron.Update(deltaSeconds);
	m_camera.Update(deltaSeconds);
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
	SetupView(size);
	m_sunlight.Setup();
		
	enableBlending();
	m_rhombicuboctahedron.Draw();
	disableBlending();
	
}

void CWindow::SetupView(const glm::ivec2 &size)
{
	glViewport(0, 0, size.x, size.y);

	// Матрица вида возвращается камерой и составляет
	// начальное значение матрицы GL_MODELVIEW.
	glLoadMatrixf(glm::value_ptr(m_camera.GetViewTransform()));

	// Матрица перспективного преобразования вычисляется функцией
	// glm::perspective, принимающей угол обзора, соотношение ширины
	// и высоты окна, расстояния до ближней и дальней плоскостей отсечения.
	const float fieldOfView = glm::radians(70.f);
	const float aspect = float(size.x) / float(size.y);
	const float zNear = 0.01f;
	const float zFar = 100.f;
	const glm::mat4 proj = glm::perspective(fieldOfView, aspect, zNear, zFar);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(glm::value_ptr(proj));
	glMatrixMode(GL_MODELVIEW);
}


void CWindow::OnKeyDown(const SDL_KeyboardEvent &event)
{
	if (m_camera.OnKeyDown(event))
	{
		return;
	}
}

void CWindow::OnKeyUp(const SDL_KeyboardEvent &event)
{
	if (m_camera.OnKeyUp(event))
	{
		return;
	}
}

void CWindow::OnDragBegin(const glm::vec2 &pos)
{
	m_camera.OnDragBegin(pos);
}
void CWindow::OnDragMotion(const glm::vec2 &pos)
{
	m_camera.OnDragMotion(pos);
}
void CWindow::OnDragEnd(const glm::vec2 &pos)
{
	m_camera.OnDragEnd(pos);
}