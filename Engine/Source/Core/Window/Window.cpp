#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "WindowManager.h"
#include "Engine.h"
#include "Core/Logger/Logger.h"
#include "GUI/GUIManager.h"
#include "Window.h"
#include "Core/Renderer/Renderer.h"

bool TextureGenEngine::Window::ShouldClose()
{
    return glfwWindowShouldClose(m_window);
}

void resizeCallback(GLFWwindow *window, int width, int height)
{
    TextureGenEngine::Window *win = (TextureGenEngine ::Window*)glfwGetWindowUserPointer(window);
    for (auto &sub : win->GetResizeSubs())
    {
        sub.callback({width, height});
    }
    TextureGenEngine::Engine::Get()->GetRenderer()->UpdateViewport(width, height);
    win->Update();
    win->Draw();
}

TextureGenEngine::Window::Window(WindowManager *manager, int id, const std::string &title, int width, int height, GLFWwindow *contextWindow) : m_manager(manager), m_id(id), m_title(title), m_width(width), m_height(height),
                                                                                                                                                         m_gui(nullptr), m_window(nullptr)
{
    if (contextWindow)
        m_window = glfwCreateWindow(width, height, title.c_str(), NULL, contextWindow);
    else
        m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    if (!m_window)
    {
        LOG_ERROR("Failed to create window\n");
        Engine::Get()->Shutdown();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(m_window);
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, resizeCallback);
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
    glClear(GL_COLOR_BUFFER_BIT);
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
    gui->SetWindow(this);
    m_resizeSubs.push_back({[gui](ResizeEvent e) { gui->Resize(e.width, e.height); }});
    gui->Init(m_width, m_height);
    m_gui = gui;
}

void TextureGenEngine::Window::GetFramebufferSize(int &width, int &height)
{
    glfwGetFramebufferSize(m_window, &width, &height);
}
