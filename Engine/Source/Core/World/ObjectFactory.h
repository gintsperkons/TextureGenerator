#pragma once

namespace TextureGenEngine
{
	class Mesh;
	namespace ObjectFactory {
		Mesh* CreateTriangle();
		Mesh *CreateSquare(int width, int height);
		Mesh* CreateCircle();
	}
}