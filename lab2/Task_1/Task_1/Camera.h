#pragma once

#include <glm/fwd.hpp>
#include <SDL2/SDL_events.h>
#include <boost/noncopyable.hpp>
#include <set>

class CCamera : private boost::noncopyable
{
public:
	explicit CCamera(float rotationRadians, float distance);

	void Update(float deltaSec);
	bool OnKeyDown(const SDL_KeyboardEvent &event);
	bool OnKeyUp(const SDL_KeyboardEvent &event);
	void OnDragBegin(const glm::vec2 &pos);
	void OnDragMotion(const glm::vec2 &pos);
	void OnDragEnd(const glm::vec2 &pos);
	glm::mat4 GetViewTransform();

private:
	float m_rotationRadiansX = 0;
	float m_rotationRadiansY = 0;

	float m_distance = 1;
	std::set<unsigned> m_keysPressed;

	glm::vec3 m_direction;
	glm::vec3 m_position;

	bool m_isRotating = false;
	glm::vec2 m_dragBeginPos;
};