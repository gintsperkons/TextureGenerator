#include <GLFW/glfw3.h>
#include "WindowManager.h"
#include "Engine.h"
#include "Core/Logger/Logger.h"
#include "GUI/GUIManager.h"
#include "Window.h"

bool TextureGenEngine::Window::ShouldClose()
{
    return glfwWindowShouldClose(m_window);
}

TextureGenEngine::Window::Window(WindowManager *manager, int id, const std::string &title, int width, int height) : m_manager(manager), m_id(id), m_title(title), m_width(width), m_height(height),
m_gui(nullptr), m_window(nullptr)
{
    m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!m_window)
    {
        LOG_ERROR("Failed to create window\n");
        Engine::Get()->Shutdown();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(m_window);
}

TextureGenEngine::Window::~Window()
{
    if (m_gui)
        delete m_gui;

    glfwDestroyWindow(m_window);
}

void TextureGenEngine::Window::Update()
{
    glfwPollEvents();
    glfwSwapBuffers(m_window);
    if (m_gui)
    {
        m_gui->Update();
    }
}

void TextureGenEngine::Window::Draw()
{
    if (m_gui)
    {
        m_gui->Draw();
    }
}

void TextureGenEngine::Window::AddGUI(TextureGenEngine::GUIManager *gui)
{
    if (m_gui)
    {
        delete m_gui;
    }
    m_gui = gui;
}
