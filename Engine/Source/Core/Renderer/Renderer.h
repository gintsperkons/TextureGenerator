#pragma once
#include <glm/glm.hpp>
#include <string>
namespace TextureGenEngine
{
	class ShaderManager;
	class Shader;
	class Renderer
	{
		glm::vec4 m_clearColor;
		ShaderManager *m_shaderManager;

	public:
		Renderer(int width, int height);
		void Clear();
		void UpdateViewport(int width, int height);
		Shader *GetShader(std::string);
		~Renderer();
	};
}