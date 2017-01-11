#pragma once
#include "ISceneObject.h"
#include <functional>
#include <vector>
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

// TODO: return glm::vec3
using Function2D = std::function<glm::vec3(float, float)>;

// ¬ершина с трЄхмерной позицией и нормалью.
struct SVertexP3N
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;

	SVertexP3N() = default;
	SVertexP3N(const glm::vec3 &position)
		: position(position)
	{
	}
};

class CSolidFunctionSurface final : public ISceneObject
{
public:
	CSolidFunctionSurface(const Function2D &fn);

	/// »нициализирует индексированную сетку треугольников
	/// @param rangeX - диапазон, где x - нижн€€ граница, y - верхн€€ граница
	/// @param rangeZ - диапазон, где x - нижн€€ граница, y - верхн€€ граница
	void Tesselate(const glm::vec2 &rangeX, const glm::vec2 &rangeZ, float step);

	// IBody interface.
	void Update(float) final {}
	void Draw() const final;
	void ChangeMode();
	void ChangeColorMode();
private:
	void CalculateColor();
private:
	Function2D m_fn;
	std::vector<SVertexP3N> m_vertices;
	std::vector<uint32_t> m_indicies;
	std::vector<glm::vec3> m_colors;
	glm::vec2 m_range;
	bool m_isFrame = false;
	bool m_isColor = false;
};