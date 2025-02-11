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
    Mesh *CreateSquare(float width, float height, float startU=.0f, float startV=.0f, float endU=1.0f, float endV=1.0f);

    Line *CreateLine(float xStart, float yStart, float xEnd, float yEnd);
		Bezier *CreateBezier(float xStart, float yStart, float xEnd, float yEnd, unsigned int segments = 100);
	}
}