#include "AABB.h"
#include "Core/Logger/Logger.h"





TextureGenEngine::AABB::AABB(Vertex2D* verticies, int size)
{
	float minX = verticies[0].Position.x;
	float maxX = verticies[0].Position.x;
	float minY = verticies[0].Position.y;
	float maxY = verticies[0].Position.y;

	
	for (int i = 1; i < size; i++)
	{
		if (verticies[i].Position.x < minX)
		{
			minX = verticies[i].Position.x;
		}
		if (verticies[i].Position.x > maxX)
		{
			maxX = verticies[i].Position.x;
		}
		if (verticies[i].Position.y < minY)
		{
			minY = verticies[i].Position.y;
		}
		if (verticies[i].Position.y > maxY)
		{
			maxY = verticies[i].Position.y;
		}
	}

	topLeft = glm::vec2(minX, maxY);
	bottomRight = glm::vec2(maxX, minY);
	LOG_DEBUG("Top left: %f, %f\n", topLeft.x, topLeft.y);
	LOG_DEBUG("Bottom right: %f, %f\n", bottomRight.x, bottomRight.y);
}

TextureGenEngine::AABB::~AABB()
{
}

bool TextureGenEngine::AABB::CheckColision(float x, float y)
{
	if (x >= topLeft.x && x <= bottomRight.x && y >= bottomRight.y && y <= topLeft.y)
	{
		return true;
	}
	return false;
}
