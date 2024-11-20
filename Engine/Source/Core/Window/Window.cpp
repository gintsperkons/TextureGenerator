#include "Window.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/Mesh.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Logger/Logger.h"
#include "Core/Asserts.h"
#include "GLFW/glfw3.h"
#include <Core/Input/MouseCodes.h>
#include <Core/Input/Input.h>
#include <iostream>

TextureGenEngine::Window::Window():Window(640, 480, "TextureGenEngine")
{
	
}

void frameBufferResizeCallback(GLFWwindow* window, int width, int height)
{
	TextureGenEngine::Window* w = (TextureGenEngine::Window*)glfwGetWindowUserPointer(window);
	w->GetRenderer()->UpdateViewport(width, height);
	w->OnResize();
	
}


void errorCallback(int error, const char* description) {
    std::cerr << "Error " << error << ": " << description << std::endl;
}

TextureGenEngine::Window::Window(int width, int height, const char* title) :
	m_renderer(nullptr),m_width(width),m_height(height)
{
	glfwSetErrorCallback(errorCallback);
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
	glfwSetFramebufferSizeCallback(m_window, frameBufferResizeCallback);
	glfwSetWindowUserPointer(m_window, this);
	glfwGetFramebufferSize(m_window, &m_width, &m_height);
	m_renderer = new Renderer(m_width, m_height);
	m_renderer->UpdateViewport(m_width, m_height);
	THAUMA_ASSERT_MSG(m_renderer!=nullptr, "Failed to create renderer");
}


TextureGenEngine::Window::~Window()
{
	delete m_renderer;
	glfwDestroyWindow(m_window);
	m_window = nullptr;
	glfwTerminate();
}

bool TextureGenEngine::Window::ShouldClose()
{
	return glfwWindowShouldClose(m_window);	
}

void TextureGenEngine::Window::Update()
{

	UpdateMouseButtons();
	SwapBuffers();
	PoolEvents();
	m_renderer->Clear();

}

void TextureGenEngine::Window::Draw()
{
	
}



void TextureGenEngine::Window::OnResize()
{
	glfwGetFramebufferSize(m_window, &m_width, &m_height);
	for (auto sub : m_resizeSubs)
	{
		ResizeEvent event;
		event.width = m_width;
		event.height = m_height;
		sub.callback(event);
	}
}

void TextureGenEngine::Window::AddResizeListener(std::function<void(ResizeEvent)> callback)
{
	ResizeSub sub;
	sub.callback = callback;
	m_resizeSubs.push_back(sub);
}






void TextureGenEngine::Window::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}

void TextureGenEngine::Window::PoolEvents()
{
	glfwPollEvents();
}

void TextureGenEngine::Window::GetFramebufferSize(int& width, int& height)
{
	if (m_window == nullptr)
	{
		LOG_ERROR("Window is null\n");
	}
	glfwGetFramebufferSize(m_window, &width, &height);

}

void TextureGenEngine::Window::UpdateMouseButtons()
{	double x,y;
	glfwGetCursorPos(m_window, &x, &y);
	Input::g_mouseDelta[0] = x - Input::g_mousePos[0];
	Input::g_mouseDelta[1] = y - Input::g_mousePos[1];
	Input::g_mousePos[0] = x;
	Input::g_mousePos[1] = y;

	for (int i = 0; i < Mouse::ButtonLast + 1; i++)
	{	
		int state = glfwGetMouseButton(m_window, i);
		if (state == GLFW_PRESS && (Input::g_mouseButtonStates[i] == Mouse::Pressed || Input::g_mouseButtonStates[i] == Mouse::Held))
		{
			Input::g_mouseButtonStates[i] = 2;
		}
		else if (state == GLFW_PRESS)
		{
			Input::g_mouseButtonStates[i] = 1;
		}
		else
		{
			Input::g_mouseButtonStates[i] = 0;
		}

	}
}
