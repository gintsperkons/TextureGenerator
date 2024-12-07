#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "WindowManager.h"
#include "Engine.h"
#include "Core/Logger/Logger.h"
#include "GUI/GUIManager.h"
#include "Window.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Input/Input.h"

bool TextureGenEngine::Window::ShouldClose()
{
    if (m_window == NULL)
        return true;
    return glfwWindowShouldClose(m_window);
    ;
}

void resizeCallback(GLFWwindow *window, int width, int height)
{
    TextureGenEngine::Window *win = (TextureGenEngine ::Window *)glfwGetWindowUserPointer(window);

    win->Resize(width, height);
    TextureGenEngine::Engine::Get()->GetRenderer()->UpdateViewport(width, height);
    win->Update();
    win->Draw();
}

TextureGenEngine::Window::Window(WindowManager *manager, int id, const std::string &title, int width, int height, GLFWwindow *contextWindow) : m_manager(manager), m_id(id), m_title(title), m_width(width), m_height(height),
                                                                                                                                               m_gui(nullptr), m_window(nullptr), m_input(nullptr)
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
    glfwSetWindowSizeLimits(m_window, 600, 400, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwSetWindowUserPointer(m_window, this);
    glfwSetFramebufferSizeCallback(m_window, resizeCallback);
    m_input = new Input(this);
}

TextureGenEngine::Window::~Window()
{
    if (m_gui)
        delete m_gui;
    if (m_input)
        delete m_input;
    if (m_window)
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

void TextureGenEngine::Window::Resize(int width, int height)
{
    m_width = width;
    m_height = height;
    for (auto &sub : m_resizeSubs)
    {
        sub.callback({width, height});
    }
}

void TextureGenEngine::Window::Scissors(int x, int y, int width, int height)
{
    glEnable(GL_SCISSOR_TEST);
    glScissor(x, y, width, height);
}

void TextureGenEngine::Window::ScissorsReset()
{
    glDisable(GL_SCISSOR_TEST);
}

void TextureGenEngine::Window::AddGUI(TextureGenEngine::GUIManager *gui)
{
    if (m_gui)
    {
        delete m_gui;
    }
    gui->SetWindow(this);
    m_resizeSubs.push_back({[gui](ResizeEvent e)
                            { gui->Resize(e.width, e.height); }});
    m_input->SubscribeToMouseClickEvents([gui](MouseButtonEvent e)
                                         { gui->MouseClick(e); });
    m_input->SubscribeToMouseMoveEvents([gui](MouseMoveEvent e)
                                        { gui->MouseMove(e); });
    gui->Init(m_width, m_height);
    m_gui = gui;
}

void TextureGenEngine::Window::GetFramebufferSize(int &width, int &height)
{
    glfwGetFramebufferSize(m_window, &width, &height);
}
