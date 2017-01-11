#pragma once
#define _USE_MATH_DEFINES
#include <math.h> 
#include <glm/vec2.hpp>
#include <vector>

class CHedgehog
{
public:
	CHedgehog();
	~CHedgehog();

	void Draw();
	void SetPosition(const glm::ivec2 & position);
private:
	void DrawNeedle();
	void DrawLegs();
	void DrawHands();
	void DrawHead();
	void DrawGlasses();
	void DrawEyes();

	glm::ivec2 m_position;
};

