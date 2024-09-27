#pragma once
#include <glm/glm.hpp>
#include "Structures/Vertex2D.h"
namespace TextureGenEngine
{
class AABB
{
	glm::vec2 topLeft;
	glm::vec2 bottomRight;

	public:
	AABB(Vertex2D* verticies, int size);
	~AABB();
	bool CheckColision(float x, float y);
};


}