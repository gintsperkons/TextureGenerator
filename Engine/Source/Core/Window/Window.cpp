#include "Window.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Logger/Logger.h"

#include "GLFW/glfw3.h"

TextureGenEngine::Window::Window():Window(640, 480, "TextureGenEngine")
{
	
}

TextureGenEngine::Window::Window(int width, int height, const char* title):
	m_renderer(nullptr)
{
	if (!glfwInit())
	{
		LOG_FATAL("Failed to initialize GLFW\n");
	}
	
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	m_window = glfwCreateWindow(640, 480, title, NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		LOG_FATAL("Failed to create window\n");
	}
	glfwMakeContextCurrent(m_window);
	m_renderer = new Renderer(width,height);
}

TextureGenEngine::Window::~Window()
{
	delete m_renderer;
	glfwTerminate();
}

bool TextureGenEngine::Window::ShouldClose()
{
	return glfwWindowShouldClose(m_window);	
}

void TextureGenEngine::Window::Update()
{
	m_renderer->Clear();

	PoolEvents();
	SwapBuffers();
}

void TextureGenEngine::Window::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}

void TextureGenEngine::Window::PoolEvents()
{
	glfwPollEvents();
}
