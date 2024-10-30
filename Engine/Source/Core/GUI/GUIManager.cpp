#include "GUIManager.h"
#include "Core/GUI/Elements/BaseElement.h"
#include "Core/Logger/Logger.h"

TextureGenEngine::GUIManager::GUIManager(int width, int height)
{
    m_width = width;
    m_height = height;
}

void TextureGenEngine::GUIManager::Draw()
{
    for (BaseElement *child : m_children)
    {

        child->Draw();
    }
}

TextureGenEngine::GUIManager::~GUIManager()
{
    for (BaseElement *child : m_children)
    {
        delete child;
    }
    m_children.clear();
}

void TextureGenEngine::GUIManager::AddChild(BaseElement* element)
{
    m_children.push_back(element);
}
