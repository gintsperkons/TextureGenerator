#include "AABB.h"
#include "Core/Logger/Logger.h"





TextureGenEngine::AABB::AABB(float* verticies, int size)
{
	float minX = verticies[0];
	float minY = verticies[1];
	float maxX = verticies[0];
	float maxY = verticies[1];

	for (int i = 0; i < size; i += 3)
	{
		if (verticies[i] < minX)
		{
			minX = verticies[i];
		}
		if (verticies[i] > maxX)
		{
			maxX = verticies[i];
		}
		if (verticies[i + 1] < minY)
		{
			minY = verticies[i + 1];
		}
		if (verticies[i + 1] > maxY)
		{
			maxY = verticies[i + 1];
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
