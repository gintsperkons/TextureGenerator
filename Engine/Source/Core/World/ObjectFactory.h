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
		Bezier* CreateBezier(Vertex3D start, Vertex3D control1, Vertex3D control2, Vertex3D end, unsigned int segments = 10);
	}
}