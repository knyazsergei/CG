#pragma once
#include "DispatchEvent.h"
#include <glm/vec2.hpp>
#include <array>
#include <vector>

class CWindow : public CAbstractInputControlWindow
{
public:
    CWindow();

    // CAbstractWindow interface
	void OnMouseDown(const SDL_MouseButtonEvent &);
	void OnMouseUp(const SDL_MouseButtonEvent &);
	void OnMouseMotion(const SDL_MouseMotionEvent &);
	void OnMouseWheel(const SDL_MouseWheelEvent &);
protected:
    void OnUpdateWindow(float deltaSeconds) override;
    void OnDrawWindow(const glm::ivec2 &size) override;

private:
    void SetupView(const glm::ivec2 &size);
    void DrawShapes();

    float m_time = 0.f;
	bool m_holding = false;
	glm::ivec2 m_windowSize;

	glm::ivec2 m_objectPosition;
	glm::ivec2 m_mousePosition;
	glm::ivec2 m_diffObjectAndMousePostion;
	glm::ivec2 m_newDiff;
};
