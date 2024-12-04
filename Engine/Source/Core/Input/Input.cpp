#include "Input.h"
#include "Core/Window/Window.h"
#include "GLFW/glfw3.h"
#include "Core/Logger/Logger.h"

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    TextureGenEngine::Window *win = (TextureGenEngine::Window *)glfwGetWindowUserPointer(window);
    win->GetInput()->KeyCallback(key, scancode, action, mods);
}

void charCallback(GLFWwindow *window, unsigned int codepoint)
{
    TextureGenEngine::Window *win = (TextureGenEngine::Window *)glfwGetWindowUserPointer(window);
    win->GetInput()->CharCallback(codepoint);
}

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    TextureGenEngine::Window *win = (TextureGenEngine::Window *)glfwGetWindowUserPointer(window);
    win->GetInput()->MouseButtonCallback(button, action, mods);
}

void cursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
    TextureGenEngine::Window *win = (TextureGenEngine::Window *)glfwGetWindowUserPointer(window);
    win->GetInput()->CursorPosCallback(xpos, ypos);
}

TextureGenEngine::Input::Input(Window * win):
m_window(win)
{
    glfwSetKeyCallback(m_window->GetWindow(), keyCallback);
    glfwSetCharCallback(m_window->GetWindow(), charCallback);
    glfwSetMouseButtonCallback(m_window->GetWindow(), mouseButtonCallback);
    glfwSetCursorPosCallback(m_window->GetWindow(), cursorPosCallback);
}

TextureGenEngine::Input::~Input()
{
}

void TextureGenEngine::Input::KeyCallback(int key, int scancode, int action, int mods)
{
    LOG_DEBUG("Key: %d, Scancode: %d, Action: %d, Mods: %d\n", key, scancode, action, mods);
}

void TextureGenEngine::Input::CharCallback(unsigned int codepoint)
{
    LOG_DEBUG("Char: %c\n", codepoint);
}

void TextureGenEngine::Input::MouseButtonCallback(int button, int action, int mods)
{
    LOG_DEBUG("Button: %d, Action: %d, Mods: %d\n", button, action, mods);
}

void TextureGenEngine::Input::CursorPosCallback(double xpos, double ypos)
{
    LOG_DEBUG("X: %f, Y: %f\n", xpos, ypos);
}
