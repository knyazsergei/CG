#include "stdafx.h" 
#include "Bodies.h" 
#include <stdint.h> 

namespace
{

	typedef glm::vec3 Vertex;

	const glm::vec3 PINK = { 1.f, 0.3f, 0.3f };
	const glm::vec3 GREEN = { 0.f, 1.f, 0.f };
	const glm::vec3 BLUE = { 0.f, 0.f, 1.f };
	const glm::vec3 PURPLE = { 1.f, 0.f, 1.f };
	const glm::vec3 CYAN = { 0.f, 0.5f, 0.7f };
	const glm::vec3 GOLD = { 0.98f, 0.85f, 0.42f };
	const glm::vec3 YELLOW = { 1.f, 1.f, 0.f };
	const glm::vec3 RED = { 1.f, 0.f, 0.f };
	const glm::vec3 WHITE = { 1.f, 1.f, 1.f };
	const glm::vec3 BLACK = { 0.f, 0.f, 0.f };

	const glm::vec3 colors[] = { PINK , GREEN, BLUE, PURPLE, CYAN, GOLD, YELLOW, RED, WHITE, BLACK };

	enum class Colors
	{
		Pink = 0,
		Green,
		Blue,
		Purple,
		Cyan,
		Gold,
		Yellow,
		Red,
		White,
		Black
	};

	struct STriangleFace
	{
		uint16_t vertexIndex1;
		uint16_t vertexIndex2;
		uint16_t vertexIndex3;
		uint16_t colorIndex;
	};

	const Vertex RHOMBICUBOCTAHEDRON_VERTICIES[] = {
		{ -0.5, -0.5, -1 },/*0*/
		{ 0.5, -0.5, -1 },/*1*/
		{ -0.5, 0.5, -1 },/*2*/
		{ 0.5, 0.5, -1 },/*3*/


		{ -1, -0.5, -0.5 },/*4*/
		{ -0.5, -1, -0.5 },/*5*/
		{ 0.5, -1, -0.5 },/*6*/
		{ 1, -0.5, -0.5 },/*7*/

		{ 1, 0.5, -0.5 },/*8*/
		{ 0.5, 1, -0.5 },/*9*/
		{ -0.5, 1, -0.5 },/*10*/
		{ -1, 0.5, -0.5 },/*11*/


		{ -1, -0.5, 0.5 },/*12*/
		{ -0.5, -1, 0.5 },/*13*/
		{ 0.5, -1, 0.5 },/*14*/
		{ 1, -0.5, 0.5 },/*15*/

		{ 1, 0.5, 0.5 },/*16*/
		{ 0.5, 1, 0.5 },/*17*/
		{ -0.5, 1, 0.5 },/*18*/
		{ -1, 0.5, 0.5 },/*19*/


		{ -0.5, -0.5, 1 },/*20*/
		{ 0.5, -0.5, 1 },/*21*/
		{ -0.5, 0.5, 1 },/*22*/
		{ 0.5, 0.5, 1 },/*23*/
	};


	const STriangleFace RHOMBICUBOCTAHEDRON_FACES[] = { // RHOMBICUBOCTAHEDRON 
		//back
		//back side
		{ 0, 1, 2, static_cast<uint16_t>(Colors::Pink) },
		{ 1, 2, 3, static_cast<uint16_t>(Colors::Pink) },

		//back left bottom side
		{ 4, 5, 0, static_cast<uint16_t>(Colors::Green) },
		//back bottom side
		{ 0, 5, 6, static_cast<uint16_t>(Colors::Purple) },
		{ 0, 6, 1, static_cast<uint16_t>(Colors::Purple) },
		//back right bottom side
		{ 1, 6, 7, static_cast<uint16_t>(Colors::Green) },
		//back right side
		{ 3, 1, 7, static_cast<uint16_t>(Colors::Gold) },
		{ 3, 7, 8, static_cast<uint16_t>(Colors::Gold) },
		//back right top
		{ 3, 8, 9, static_cast<uint16_t>(Colors::Cyan) },
		//back top
		{ 10, 3, 9, static_cast<uint16_t>(Colors::Purple) },
		{ 10, 2, 3, static_cast<uint16_t>(Colors::Purple) },
		//back left top
		{ 11, 2, 10, static_cast<uint16_t>(Colors::Cyan) },
		//back left side
		{ 11, 0, 2, static_cast<uint16_t>(Colors::Gold) },
		{ 11, 4, 0, static_cast<uint16_t>(Colors::Gold) },

		//left side
		{ 12, 4, 11, static_cast<uint16_t>(Colors::Pink) },
		{ 12, 11, 19, static_cast<uint16_t>(Colors::Pink) },
		//left bottom side
		{ 12, 13, 5, static_cast<uint16_t>(Colors::Purple) },
		{ 12, 5, 4, static_cast<uint16_t>(Colors::Purple) },
		//left top side
		{ 19, 11, 10, static_cast<uint16_t>(Colors::Purple) },
		{ 19, 10, 18, static_cast<uint16_t>(Colors::Purple) },



		//bottom
		//bottom side
		{ 13, 14, 6, static_cast<uint16_t>(Colors::Pink) },
		{ 13, 6, 5, static_cast<uint16_t>(Colors::Pink) },


		//right
		//right side
		{ 15, 16, 8, static_cast<uint16_t>(Colors::Pink) },
		{ 15, 8, 7, static_cast<uint16_t>(Colors::Pink) },

		//right bottom side
		{ 14, 15, 7, static_cast<uint16_t>(Colors::Purple) },
		{ 14, 7, 6, static_cast<uint16_t>(Colors::Purple) },

		//right top side
		{ 16, 17, 9, static_cast<uint16_t>(Colors::Purple) },
		{ 16, 9, 8, static_cast<uint16_t>(Colors::Purple) },


		//top side
		{ 18, 10, 9, static_cast<uint16_t>(Colors::Pink) },
		{ 18, 17, 9, static_cast<uint16_t>(Colors::Pink) },
		//{ 12, 4, 11, static_cast<uint16_t>(Colors::Black) },
		//{ 12, 11, 19, static_cast<uint16_t>(Colors::Black) },

		//front
		//front side
		{ 20, 21, 22, static_cast<uint16_t>(Colors::Pink) },
		{ 21, 22, 23, static_cast<uint16_t>(Colors::Pink) },

		//front bottom left
		{ 12, 13, 20, static_cast<uint16_t>(Colors::Green) },
		//front bottom side
		{ 20, 13, 14, static_cast<uint16_t>(Colors::Purple) },
		{ 20, 14, 21, static_cast<uint16_t>(Colors::Purple) },
		//front bottom right
		{ 21, 14, 15, static_cast<uint16_t>(Colors::Green) },

		//front right side
		{ 23, 21, 15, static_cast<uint16_t>(Colors::Gold) },
		{ 23, 15, 16, static_cast<uint16_t>(Colors::Gold) },

		//front top right
		{ 23, 16, 17, static_cast<uint16_t>(Colors::Cyan) },

		//front top side
		{ 18, 23, 17, static_cast<uint16_t>(Colors::Purple) },
		{ 18, 22, 23, static_cast<uint16_t>(Colors::Purple) },

		//front top left
		{ 19, 22, 18, static_cast<uint16_t>(Colors::Cyan) },
		//front left side
		{ 19, 20, 22, static_cast<uint16_t>(Colors::Gold) },
		{ 19, 12, 20, static_cast<uint16_t>(Colors::Gold) },

		
	};

}

CRhombicuboctahedron::CRhombicuboctahedron()
	: m_alpha(1)
{
}

void CRhombicuboctahedron::Update(float deltaTime)
{
	(void)deltaTime;
}

void CRhombicuboctahedron::Draw() const
{
	if (m_alpha < 0.99f)
	{
		glFrontFace(GL_CW);
		OutputFaces();
		glFrontFace(GL_CCW);
	}
	OutputFaces();
}

void CRhombicuboctahedron::SetAlpha(float alpha)
{
	m_alpha = alpha;
}

void CRhombicuboctahedron::OutputFaces() const
{
	for (const STriangleFace &face : RHOMBICUBOCTAHEDRON_FACES)
	{
		glBegin(GL_TRIANGLES);
		const Vertex &v1 = RHOMBICUBOCTAHEDRON_VERTICIES[face.vertexIndex1];
		const Vertex &v2 = RHOMBICUBOCTAHEDRON_VERTICIES[face.vertexIndex2];
		const Vertex &v3 = RHOMBICUBOCTAHEDRON_VERTICIES[face.vertexIndex3];
		glm::vec3 normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));
		glm::vec3 color = colors[face.colorIndex];

		glColor4f(color.x, color.y, color.z, m_alpha);
		glNormal3fv(glm::value_ptr(normal));
		glVertex3fv(glm::value_ptr(v1));
		glVertex3fv(glm::value_ptr(v2));
		glVertex3fv(glm::value_ptr(v3));
		glEnd();
	}
}