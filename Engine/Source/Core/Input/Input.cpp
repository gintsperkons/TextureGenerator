#include "Input.h"
#include "Core/Window/Window.h"
#include "GLFW/glfw3.h"
#include "Core/Logger/Logger.h"
#include "Engine.h"

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
    for (auto &sub : m_keyEventSubs)
    {
        sub.callback({key, scancode, action, mods});
    }
}

void TextureGenEngine::Input::CharCallback(unsigned int codepoint)
{
    for (auto &sub : m_charEventSubs)
    {
        sub.callback({codepoint});
    }
}

void TextureGenEngine::Input::MouseButtonCallback(int button, int action, int mods)
{
    double x,y;
    glfwGetCursorPos(m_window->GetWindow(), &x, &y);
    y = m_window->GetHeight()-y;
    for (auto &sub : m_mouseClickSubs)
    {
        sub.callback({x, y, button, action == GLFW_PRESS});
    }
}

void TextureGenEngine::Input::CursorPosCallback(double xpos, double ypos)
{
    m_xChange = xpos - m_xLast;
    m_yChange = ypos - m_yLast;
    m_xLast = xpos;
    m_yLast = ypos;
    for (auto &sub : m_mouseMoveSubs)
    {
        sub.callback({m_xChange, m_yChange});
    }
}

void TextureGenEngine::Input::SubscribeToMouseClickEvents(std::function<void(MouseButtonEvent)> subscriber)
{
    MouseClickSub sub;
    sub.callback = subscriber;
    m_mouseClickSubs.push_back(sub);
}

void TextureGenEngine::Input::SubscribeToMouseMoveEvents(std::function<void(MouseMoveEvent)> subscriber)
{
    MouseMoveSub sub;
    sub.callback = subscriber;
    m_mouseMoveSubs.push_back(sub);
}

void TextureGenEngine::Input::SubscribeToCharEvents(std::function<void(CharEvent)> subscriber)
{
    CharEventSub sub;
    sub.callback = subscriber;
    m_charEventSubs.push_back(sub);
}

void TextureGenEngine::Input::SubscribeToKeyEvents(std::function<void(KeyEvent)> subscriber)
{
    KeyEventSub sub;
    sub.callback = subscriber;
    m_keyEventSubs.push_back(sub);
}

void TextureGenEngine::Input::OnKeyPress(std::function<void(KeyEvent)> subscriber,Window* win)
{
    win->GetInput()->SubscribeToKeyEvents(subscriber);
}

void TextureGenEngine::Input::GetMousePosition(double &x, double &y)
{
    glfwGetCursorPos(m_window->GetWindow(), &x, &y);
    y = m_window->GetHeight()-y;
}
