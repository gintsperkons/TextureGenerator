#include "GUIManager.h"
#include "Components/Component.h"

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
