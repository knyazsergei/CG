#pragma once

#include "AbstractWindow.h"

class IInputEventAcceptor;
namespace sdl
{
	// ��������� ��������������� ������� SDL �� ����������.
	void DispatchEvent(const SDL_Event & event, IInputEventAcceptor & acceptor);
}

// ��������� ������� SDL, ���������� �� ����������.
// ������� �������� � ����� ���� ��������.
class IInputEventAcceptor
{
public:
	virtual ~IInputEventAcceptor() = default;

	virtual void OnDragBegin(const glm::vec2 &pos) { (void)pos; }
	virtual void OnDragMotion(const glm::vec2 &pos) { (void)pos; }
	virtual void OnDragEnd(const glm::vec2 &pos) { (void)pos; }
	virtual void OnKeyDown(const SDL_KeyboardEvent &) {}
	virtual void OnKeyUp(const SDL_KeyboardEvent &) {}
};

// ����, ����������� ��������������� ������� SDL
class CAbstractInputControlWindow
	: public CAbstractWindow
	, public IInputEventAcceptor
{
protected:
	void OnWindowEvent(const SDL_Event &event) final
	{
		sdl::DispatchEvent(event, *this);
	}
};