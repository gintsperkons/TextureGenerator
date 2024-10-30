#pragma once

namespace TextureGenEngine
{
	class Mesh;
	namespace ObjectFactory {
		Mesh* CreateTriangle();
		Mesh *CreateSquare(int x, int y, int width, int height);
		Mesh* CreateCircle();
	}
}