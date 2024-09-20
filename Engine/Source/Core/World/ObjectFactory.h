#pragma once

namespace TextureGenEngine
{
	class Mesh;
	namespace ObjectFactory {
		Mesh* CreateTriangle();
		Mesh* CreateSquare();
		Mesh* CreateCircle();
	}
}