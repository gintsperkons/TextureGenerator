#pragma once
#include <glm/glm.hpp>
namespace TextureGenEngine
{
class AABB
{
	glm::vec2 topLeft;
	glm::vec2 bottomRight;

	public:
	AABB(float* verticies, int size);
	~AABB();
	bool CheckColision(float x, float y);
};


}