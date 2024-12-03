#include "GUIManager.h"
#include "Components/Component.h"
#include "Core/Logger/Logger.h"

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
    LOG_DEBUG("Resizing GUIManager to %d %d\n", width, height);
}
