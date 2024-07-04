#include <GLFW/glfw3.h>
#include "Window.h"

TextureGen::Window::Window(/* args */)
{
    Window(800, 600, "Test Name");
}

TextureGen::Window::Window(int width, int height, const char *title)
{
    if (!glfwInit())
    {
        glfwTerminate();
    }
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

void TextureGen::Window::PollEvents()
{
    glfwPollEvents();
}

TextureGen::Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}
