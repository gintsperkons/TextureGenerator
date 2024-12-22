#pragma once
#include "Defines.h"
#include "Core/Renderer/Structures/Vertex3D.h"
namespace TextureGenEngine
{
	class Mesh;
	class Line;
	class Bezier;
	namespace ObjectFactory {
		Mesh* CreateTriangle();
		Mesh *CreateSquare(int width, int height);
		Mesh* CreateCircle();

		Line* CreateLine(int xStart, int yStart, int xEnd, int yEnd);
		Bezier *CreateBezier(int xStart, int yStart, int xEnd, int yEnd, unsigned int segments = 100);
	}
}