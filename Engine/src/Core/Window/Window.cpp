#include <GLFW/glfw3.h>
#include "Window.h"

TextureGen::Window::Window() : Window(800, 600, "Test Name")
{
    // Constructor body, if needed
}

TextureGen::Window::Window(int width, int height, const char *title)
{
    if (!glfwInit())
    {
        glfwTerminate();
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    m_window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
    }
    glfwMakeContextCurrent(m_window);
}

bool TextureGen::Window::ShouldClose()
{
    return glfwWindowShouldClose(m_window);
}

GLFWwindow *TextureGen::Window::GetWindow()
{
    return m_window;
}

void TextureGen::Window::PollEvents()
{
    glfwPollEvents();
}

TextureGen::Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
