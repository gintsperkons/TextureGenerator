#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer.h"
#include "Core/Logger/Logger.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Core/Renderer/Shaders/ShaderManager.h>
#include <Core/Renderer/Shaders/Shader.h>

TextureGenEngine::Renderer::Renderer(int width, int height) : m_clearColor(0.0f, 0.0f, 0.0f, 1.0f)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_FATAL("Failed to initialize GLAD");
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glViewport(0, 0, width, height);
	m_projectionMatrix = glm::ortho(0.0f, (float)width,0.0f , (float)height, -1.0f, 1.0f);
	m_shaderManager = new ShaderManager();
}

void TextureGenEngine::Renderer::Clear()
{
	glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
}

void TextureGenEngine::Renderer::UpdateViewport(int width, int height)
{
	glViewport(0, 0, width, height);
	m_projectionMatrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);
}

TextureGenEngine::Shader* TextureGenEngine::Renderer::GetShader(std::string name)
{
	if (!m_shaderManager) return nullptr;
	return m_shaderManager->GetShader(name);
}

TextureGenEngine::Renderer::~Renderer()
{
	delete m_shaderManager;
}
