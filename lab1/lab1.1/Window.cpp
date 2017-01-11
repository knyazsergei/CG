#include "stdafx.h"
#include "Window.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/vec2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace
{

void StrokeShedule(const glm::ivec2 &size)
{
	const float STEP = 10.f;
	const float LINE_SIZE = 5.f;


	//horizontal stroke

	glBegin(GL_LINE_STRIP);
	glVertex2f(0, size.y * 0.5f);
	glVertex2f(float(size.x), size.y * 0.5f);
	glEnd();

	for(float point = 0; point <= size.x; point += STEP)
	{
		glBegin(GL_LINE_STRIP);
		glVertex2f(point, size.y * 0.5f - LINE_SIZE);
		glVertex2f(point, size.y * 0.5f + LINE_SIZE);
		glEnd();
	}

	//vertical stroke

	glBegin(GL_LINE_STRIP);
	glVertex2f(size.x * 0.5f, 0);
	glVertex2f(size.x * 0.5f, float(size.y));
	glEnd();

	for (float point = 0; point <= size.y; point += STEP)
	{
		glBegin(GL_LINE_STRIP);
		glVertex2f(size.x * 0.5f - LINE_SIZE, point);
		glVertex2f(size.x * 0.5f + LINE_SIZE, point);
		glEnd();
	}
}

// Рисуем архимедову спираль
void DrawArchimedeanSpiral(const glm::ivec2 &size, bool clockwiseDirection, float zoom = 1 )
{	
	float step = (clockwiseDirection ? -1 : 1) * 0.1f;

	double phi;

	auto width = size.x;
	auto height = size.y;
	
	float x = 1.f;
	float y = 1.f;

	glBegin(GL_LINE_STRIP);

	for (size_t i = 0; x > 0 && y > 0 && x < width && y < height; i++)
	{
		phi = i * step;

		x = width * 0.5f + zoom * float(phi * cos(phi));
		y = height * 0.5f - zoom * float(phi * sin(phi));
	
		glVertex2f(x, y);
	}
	glEnd();
}
}

CWindow::CWindow()
{
    SetBackgroundColor({255.f, 255.f, 255.f, 1.f});
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
    m_time += deltaSeconds;
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
    SetupView(size);


	// Рисуем координатную плоскость
	glColor3f(0, 0, 0);
	StrokeShedule(size);

	//Рисуем архимедову спираль
	glColor3f(0, 0, 0);
	DrawArchimedeanSpiral(size, false, 10);
}

void CWindow::SetupView(const glm::ivec2 &size)
{
    // Матрица ортографического проецирования изображения в трёхмерном пространстве
    // из параллелипипеда с размером, равным (size.X x size.Y x 2).
    const glm::mat4 matrix = glm::ortho<float>(0, float(size.x), float(size.y), 0);
    glViewport(0, 0, size.x, size.y);
    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(glm::value_ptr(matrix));
    glMatrixMode(GL_MODELVIEW);
}
