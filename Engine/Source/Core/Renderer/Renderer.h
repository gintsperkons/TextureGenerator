#pragma once
#include <glm/glm.hpp>
#include <string>
namespace TextureGenEngine
{
	class ShaderManager;
	class Shader;
	class Renderer
	{
		int m_width, m_height;
		glm::vec4 m_clearColor;
		ShaderManager *m_shaderManager;
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;

	public:
		Renderer(int width, int height);
		void Clear();
		void UseCustomViewport(int x, int y, int width, int height);
		void UpdateViewport(int width, int height);
		void UseDefaultViewport();
		Shader *GetShader(std::string);
		glm::mat4 GetProjectionMatrix() { return m_projectionMatrix; }
		glm::mat4 GetViewMatrix() { return m_viewMatrix; }
		~Renderer();
	};
}