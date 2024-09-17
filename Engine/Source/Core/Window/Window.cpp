#include "Window.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Logger/Logger.h"
#include "Core/Asserts.h"
#include "GLFW/glfw3.h"

TextureGenEngine::Window::Window():Window(640, 480, "TextureGenEngine")
{
	
}

void frameBufferResizeCallback(GLFWwindow* window, int width, int height)
{
	TextureGenEngine::Window* w = (TextureGenEngine::Window*)glfwGetWindowUserPointer(window);
	w->GetRenderer()->UpdateViewport(width, height);
	w->OnResize();
	
}

TextureGenEngine::Window::Window(int width, int height, const char* title) :
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
	glfwSetFramebufferSizeCallback(m_window, frameBufferResizeCallback);
	glfwSetWindowUserPointer(m_window, this);
	glfwGetFramebufferSize(m_window, &width, &height);
	m_renderer = new Renderer(width, height);
	THAUMA_ASSERT_DEBUG(m_renderer, "Failed to create renderer");
	m_mesh = new Mesh();
}


TextureGenEngine::Window::~Window()
{
	delete m_mesh;
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
	SwapBuffers();
	PoolEvents();
	m_renderer->Clear();

}

void TextureGenEngine::Window::Draw()
{
	m_mesh->Draw();
}

void TextureGenEngine::Window::OnResize()
{
	int width, height;
	glfwGetFramebufferSize(m_window, &width, &height);
	for (auto sub : m_resizeSubs)
	{
		ResizeEvent event;
		event.width = width;
		event.height = height;
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
