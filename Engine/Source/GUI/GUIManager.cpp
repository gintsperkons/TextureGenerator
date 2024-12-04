#include "GUIManager.h"
#include "Components/Component.h"
#include "Core/Logger/Logger.h"
#include "Core/Input/InputEvents.h"
#include "Core/Window/Window.h"
#include "Core/Input/Input.h"

TextureGenEngine::GUIManager::GUIManager()
{
}

TextureGenEngine::GUIManager::~GUIManager()
{
    for (auto &child : m_children)
    {
        delete child;
    }
    m_children.clear();
}

void TextureGenEngine::GUIManager::Update()
{
}

void TextureGenEngine::GUIManager::Draw()
{
    for (auto &child : m_children)
    {
        child->Draw();
    }
}

void TextureGenEngine::GUIManager::AddComponent(Component *component)
{   component->SetManager(this);
    m_children.push_back(component);
}

void TextureGenEngine::GUIManager::Resize(int width, int height)
{
    m_oldWidth = m_width;
    m_oldHeight = m_height;
    m_width = width;
    m_height = height;
    LOG_DEBUG("Resizing GUIManager to %d %d\n", width, height);
    for (auto &child : m_children)
    {
        child->Resize(width, height);
    }
}

void TextureGenEngine::GUIManager::Init(int width, int height)
{
    m_oldWidth = m_width;
    m_oldHeight = m_height;
    m_width = width;
    m_height = height;
    if (m_oldWidth == 0 && m_oldHeight == 0)
    {
        m_oldWidth = width;
        m_oldHeight = height;
    }
    for (auto &child : m_children)
    {
        child->Init(width, height);
    }

    m_window->GetInput()->SubscribeToMouseClickEvents([this](MouseButtonEvent e) {
        for (auto &child : m_children)
        {
            LOG_DEBUG("Mouse move event\n");
            LOG_DEBUG("Event x: %d, y: %d, button: %d, down: %d\n", e.x, e.y, e.button, e.down);
            //child->OnMouseMove(e);
        }
    });
}

void TextureGenEngine::GUIManager::GetOldSize(float &width, float &height)
{
    width = m_oldWidth;
    height = m_oldHeight;
}
