#pragma once

namespace TextureGenEngine
{
	class Mesh;
	class Line;
	namespace ObjectFactory {
		Mesh* CreateTriangle();
		Mesh *CreateSquare(int width, int height);
		Mesh* CreateCircle();

		Line* CreateLine(int xStart, int yStart, int xEnd, int yEnd);
	}
}