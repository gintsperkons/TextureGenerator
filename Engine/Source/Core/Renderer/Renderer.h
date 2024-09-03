#pragma once
#include <glm/glm.hpp>
namespace TextureGenEngine
{
	class Renderer {
		glm::vec4 m_clearColor;
	public:
		Renderer(int width, int height);
		void Clear();
		void UpdateViewport(int width, int height);
		~Renderer();
	};
}