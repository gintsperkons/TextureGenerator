#include "WindowManager.h"
#include <GLFW/glfw3.h>
#include "Core/Logger/Logger.h"
#include "Engine.h"
#include "Window.h"

bool TextureGenEngine::WindowManager::ShouldClose()
{
    if (m_mainWindow)
    {
        return m_mainWindow->ShouldClose() || activeWindow == 0;
    }
    return true;
}

// Public
TextureGenEngine::WindowManager::WindowManager()
{

    if (!glfwInit())
    {
        LOG_ERROR("Failed to initialize GLFW\n");
        Engine::Get()->Shutdown();
        exit(EXIT_FAILURE);
    }
    m_mainWindow = AddWindow("TextureGenEngine", 800, 600);
}





TextureGenEngine::WindowManager::~WindowManager()
{
    for (Window *window : m_windows)
    {
        delete window;
    }
    m_windows.clear();
    glfwTerminate();
}

void TextureGenEngine::WindowManager::Update()
{
    for (Window *window : m_windows)
    {
        window->Update();
    }
    CloseNecessaryWindows();
}

void TextureGenEngine::WindowManager::Draw()
{
    for (Window *window : m_windows)
    {
        window->Draw();
    }
}

TextureGenEngine::Window *TextureGenEngine::WindowManager::AddWindow(const std::string &title, int width, int height)
{

    Window *window = new Window(this, m_lastId, title, width, height, m_mainWindow ? m_mainWindow->GetWindow() : nullptr);
    if (window)
    {
        m_windows.push_back(window);
        m_lastId++;
        activeWindow++;
        return window;
    }
    return nullptr;
}

TextureGenEngine::Window *TextureGenEngine::WindowManager::GetMainWindow()
{
    return m_mainWindow;
}

//Private
void TextureGenEngine::WindowManager::CloseNecessaryWindows()
{
    std::vector<int> toRemove;
    for (int i = 0; i < m_windows.size(); i++)
    {
        if (m_windows[i]->ShouldClose())
        {
            toRemove.push_back(i);
        }
    }
    for (int i = 0; i < toRemove.size(); i++)
    {
        delete m_windows[toRemove[i]];
        m_windows.erase(m_windows.begin() + toRemove[i]);
        activeWindow--;
    }
}