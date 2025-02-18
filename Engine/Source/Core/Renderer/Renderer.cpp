#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Renderer.h"
#include "Core/Logger/Logger.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <Core/Renderer/Shaders/ShaderManager.h>
#include <Core/Renderer/Shaders/Shader.h>

float near = -1.f;
float far = 1.f;

TextureGenEngine::Renderer::Renderer(int width, int height) : m_clearColor(1.0f, 0.5f, 1.0f, 1.0f)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		LOG_FATAL("Failed to initialize GLAD");
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glEnable(GLFW_CONTEXT_DEBUG);
	glfwSetErrorCallback([](int error, const char *description)
						 { LOG_ERROR("GLFW Error: %s\n", description); });

	glViewport(0, 0, width, height);
	m_projectionMatrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height, near, far);
	m_viewMatrix = glm::mat4(1.0f);
	m_shaderManager = new ShaderManager();
}

void TextureGenEngine::Renderer::Clear()
{
	glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
}

void TextureGenEngine::Renderer::UseCustomViewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
	m_projectionMatrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height, near, far);
}

void TextureGenEngine::Renderer::UpdateViewport(int width, int height)
{
	m_width = width;
	m_height = height;
	glViewport(0, 0, m_width, m_height);
	m_projectionMatrix = glm::ortho(0.0f, (float)m_width, 0.0f, (float)m_height, near, far);
}

void TextureGenEngine::Renderer::UseDefaultViewport()
{
	glViewport(0, 0, m_width, m_height);
	m_projectionMatrix = glm::ortho(0.0f, (float)m_width, 0.0f, (float)m_height, near, far);
}

TextureGenEngine::Shader *TextureGenEngine::Renderer::GetShader(std::string name)
{
	if (!m_shaderManager)
		return nullptr;
	return m_shaderManager->GetShader(name);
}

TextureGenEngine::Renderer::~Renderer()
{
	if (m_shaderManager)
		delete m_shaderManager;
	m_shaderManager == nullptr;
}
