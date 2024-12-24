#pragma once
#include "Defines.h"
#include "Core/Renderer/Structures/Vertex3D.h"
namespace TextureGenEngine
{
	class Mesh;
	class Line;
	class Bezier;
	namespace ObjectFactory
	{
		Mesh *CreateTriangle();
		Mesh *CreateSquare(float width, float height);

		Line *CreateLine(float xStart, float yStart, float xEnd, float yEnd);
		Bezier *CreateBezier(float xStart, float yStart, float xEnd, float yEnd, unsigned int segments = 100);
	}
}