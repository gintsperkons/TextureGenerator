#include "Window.h"
#include "Core/Logger/Logger.h"

#include "GLFW/glfw3.h"

TextureGenEngine::Window::Window():Window(640, 480, "TextureGenEngine")
{
	
}

TextureGenEngine::Window::Window(int width, int height, const char* title)
{
	if (!glfwInit())
	{
		LOG_FATAL("Failed to initialize GLFW\n");
	}
	m_window = glfwCreateWindow(640, 480, title, NULL, NULL);
	if (!m_window)
	{
		glfwTerminate();
		LOG_FATAL("Failed to create window\n");
	}
	glfwMakeContextCurrent(m_window);
}

TextureGenEngine::Window::~Window()
{
	glfwTerminate();
}

bool TextureGenEngine::Window::ShouldClose()
{
	return glfwWindowShouldClose(m_window);	
}

void TextureGenEngine::Window::PoolEvents()
{
	glfwPollEvents();
}
