#include "stdafx.h"
#include "Hedgehog.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace
{
	// Рисуем закрашенный эллипс
	void FillEllipse(float xCenter, float yCenter, float rx, float ry, int pointCount = 360)
	{
		const float step = float(2 * M_PI) / pointCount;

		// Эллипс представлет в виде "веера" из треугольников
		glBegin(GL_TRIANGLE_FAN);
		// Начальная точка веера располагается в центре эллипса
		glVertex2f(xCenter, yCenter);
		// Остальные точки - равномерно по его границе
		for (float angle = 0; angle <= float(2 * M_PI); angle += step)
		{
			float a = (fabsf(angle - float(2 * M_PI)) < 0.00001f) ? 0.f : angle;
			const float dx = rx * cosf(a);
			const float dy = ry * sinf(a);
			glVertex2f(dx + xCenter, dy + yCenter);
		}
		glEnd();
	}

	//Рисуем закрашеный круг
	void FillCircle(float xCenter, float yCenter, float r)
	{
		FillEllipse(xCenter, yCenter, r, r);
	}

	//Рисуем закрашенный полигон
	void FillPolygon(const std::vector<glm::ivec2> & coordinates)
	{
		glBegin(GL_TRIANGLE_FAN);
		for (auto coordinate : coordinates)
		{
			glVertex2f(float(coordinate.x), float(coordinate.y));
		}
		glEnd();
	}
}


void SetGlColor3fRGB(float r, float g, float b)
{
	glColor3f(r * 0.004f, g * 0.004f, b * 0.004f);
}


CHedgehog::CHedgehog()
{
}


CHedgehog::~CHedgehog()
{
}

void CHedgehog::Draw()
{
	DrawNeedle();
	DrawLegs();
	DrawHands();
	DrawHead();
	DrawGlasses();
	DrawEyes();
}

void CHedgehog::SetPosition(const glm::ivec2 & position)
{
	m_position = position;
}

void CHedgehog::DrawNeedle()
{
	//Рисуем иголки
	SetGlColor3fRGB(139, 47, 146);
	FillPolygon({
		glm::ivec2(m_position.x, m_position.y),
		glm::ivec2(m_position.x + -80, m_position.y + 11),
		glm::ivec2(m_position.x + -130, m_position.y - 35),
		glm::ivec2(m_position.x + -75, m_position.y - 50),
		glm::ivec2(m_position.x + -85, m_position.y - 120),
		glm::ivec2(m_position.x + -30, m_position.y - 90),
		glm::ivec2(m_position.x, m_position.y - 140),
		glm::ivec2(m_position.x - -30, m_position.y - 90),
		glm::ivec2(m_position.x - -85, m_position.y - 120),
		glm::ivec2(m_position.x - -75, m_position.y - 50),
		glm::ivec2(m_position.x - -130, m_position.y - 35),
		glm::ivec2(m_position.x - -80, m_position.y + 11),
		glm::ivec2(m_position.x, m_position.y),
	});
}

void CHedgehog::DrawLegs()
{
	//Ноги
	//Левая
	FillPolygon({
		glm::ivec2(m_position.x - 13, m_position.y + 70),
		glm::ivec2(m_position.x - 12, m_position.y + 97),
		glm::ivec2(m_position.x, m_position.y + 120),
		glm::ivec2(m_position.x - 4, m_position.y + 123),
		glm::ivec2(m_position.x - 32, m_position.y + 125),
		glm::ivec2(m_position.x - 40, m_position.y + 117),
		glm::ivec2(m_position.x - 12, m_position.y + 111),
		glm::ivec2(m_position.x - 30, m_position.y + 107),
		glm::ivec2(m_position.x - 27, m_position.y + 87),
		glm::ivec2(m_position.x - 25, m_position.y + 70),
	});
	//Правая
	FillPolygon({
		glm::ivec2(m_position.x + 13, m_position.y + 70),
		glm::ivec2(m_position.x + 12, m_position.y + 97),
		glm::ivec2(m_position.x, m_position.y + 120),
		glm::ivec2(m_position.x + 4, m_position.y + 123),
		glm::ivec2(m_position.x + 32, m_position.y + 125),
		glm::ivec2(m_position.x + 40, m_position.y + 117),
		glm::ivec2(m_position.x + 12, m_position.y + 111),
		glm::ivec2(m_position.x + 30, m_position.y + 107),
		glm::ivec2(m_position.x + 27, m_position.y + 87),
		glm::ivec2(m_position.x + 25, m_position.y + 70),
	});

}

void CHedgehog::DrawHands()
{
	//Руки
	//Левая
	SetGlColor3fRGB(238, 83, 135);
	FillPolygon({
		glm::ivec2(m_position.x - 70, m_position.y + 30),
		glm::ivec2(m_position.x - 125, m_position.y + 20),
		glm::ivec2(m_position.x - 120, m_position.y + 5),
		glm::ivec2(m_position.x - 110, m_position.y + 5),
		glm::ivec2(m_position.x - 75, m_position.y + 10),
	});
	//Правая
	FillPolygon({
		glm::ivec2(m_position.x + 70, m_position.y + 30),
		glm::ivec2(m_position.x + 125, m_position.y + 20),
		glm::ivec2(m_position.x + 120, m_position.y + 5),
		glm::ivec2(m_position.x + 110, m_position.y + 5),
		glm::ivec2(m_position.x + 75, m_position.y + 10),
	});
}

void CHedgehog::DrawHead()
{
	//Рисуем силуэт головы
	SetGlColor3fRGB(238, 83, 125);
	FillCircle(float(m_position.x), float(m_position.y), 80.f);

	//Рисуем рот
	SetGlColor3fRGB(193, 40, 68);
	FillEllipse(float(m_position.x), m_position.y + 10.f, 15.f, 37.f);
	SetGlColor3fRGB(238, 83, 125);
	FillEllipse(float(m_position.x), float(m_position.y), 20.f, 35.f);

	//Рисуем нос
	SetGlColor3fRGB(193, 40, 68);
	FillPolygon({
		glm::ivec2(m_position.x - 8, m_position.y - 9),
		glm::ivec2(m_position.x - 2, m_position.y + 11),
		glm::ivec2(m_position.x + 2, m_position.y + 11),
		glm::ivec2(m_position.x + 8, m_position.y - 9),
	});

}

void CHedgehog::DrawGlasses()
{
	//Очки
	SetGlColor3fRGB(99, 45, 103);
	//левая линза
	FillCircle(m_position.x - 30.f, m_position.y - 10.f, 30.f);
	//правая линза
	FillCircle(m_position.x + 30.f, m_position.y - 10.f, 30.f);

	//Левая оправа
	FillPolygon({ glm::ivec2(m_position.x - 20, m_position.y - 15),
		glm::ivec2(m_position.x - 25, m_position.y - 10),
		glm::ivec2(m_position.x - 68, m_position.y - 40),
		glm::ivec2(m_position.x - 60, m_position.y - 53) });
	//Правая оправа 
	FillPolygon({ glm::ivec2(m_position.x + 20, m_position.y - 15),
		glm::ivec2(m_position.x + 25, m_position.y - 10),
		glm::ivec2(m_position.x + 68, m_position.y - 40),
		glm::ivec2(m_position.x + 60, m_position.y - 53) });
}

void CHedgehog::DrawEyes()
{
	//Глазные яблоки
	SetGlColor3fRGB(255, 255, 255);
	//левое
	FillCircle(float(m_position.x - 30), float(m_position.y - 10), 22.f);
	//правое
	FillCircle(float(m_position.x + 30), float(m_position.y - 10), 22.f);
	//Зрачки
	SetGlColor3fRGB(0, 5, 2);
	//левый
	FillEllipse(float(m_position.x - 20), float(m_position.y - 7), 10.f, 10.f);
	//правый
	FillEllipse(float(m_position.x + 20), float(m_position.y - 7), 10.f, 10.f);

}
