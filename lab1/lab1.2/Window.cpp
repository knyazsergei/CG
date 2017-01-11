#include "stdafx.h"
#include "Window.h"
#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Hedgehog.h"
#include <iostream>

CWindow::CWindow()
{
    SetBackgroundColor({255.f, 255.f, 255.f, 1.f});
}

void CWindow::OnMouseDown(const SDL_MouseButtonEvent & btn)
{
	if (btn.type == SDL_MOUSEBUTTONDOWN && btn.button == SDL_BUTTON_LEFT)
	{
		glm::ivec2 vec({ 
			m_mousePosition.x - m_objectPosition.x - m_newDiff.x, 
			m_mousePosition.y - m_objectPosition.y - m_newDiff.y 
		});

		if(sqrt(pow(vec.x, 2)+ pow(vec.y, 2)) < 100)
		{
			m_holding = true;
			m_diffObjectAndMousePostion = vec;
		}
	}
}

void CWindow::OnMouseUp(const SDL_MouseButtonEvent & btn)
{
	if (btn.type == SDL_MOUSEBUTTONUP && btn.button == SDL_BUTTON_LEFT)
	{
		m_holding = false;
	}
}

void CWindow::OnMouseMotion(const SDL_MouseMotionEvent & motion)
{
	m_mousePosition = glm::ivec2(motion.x, motion.y);
}

void CWindow::OnMouseWheel(const SDL_MouseWheelEvent & wheel)
{
}

void CWindow::OnUpdateWindow(float deltaSeconds)
{
    m_time += deltaSeconds;
}

void CWindow::OnDrawWindow(const glm::ivec2 &size)
{
	SetupView(size);

	double zoom = 1;

	if (m_holding)
	{
		m_newDiff = { m_mousePosition.x - m_diffObjectAndMousePostion.x, m_mousePosition.y - m_diffObjectAndMousePostion.y };
	}
	glLoadIdentity();
	glTranslatef(m_objectPosition.x + m_newDiff.x , m_objectPosition.y + m_newDiff.y, zoom);
	
	CHedgehog hedgehog;
	hedgehog.SetPosition(m_objectPosition);
	hedgehog.Draw();

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

	m_windowSize = size;
}
