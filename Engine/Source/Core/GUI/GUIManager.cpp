#include "GUIManager.h"
#include "Core/GUI/SubElements/BaseElement.h"
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

void TextureGenEngine::GUIManager::Click(int x, int y)
{
    for (BaseElement *child : m_children)
    {
        child->CheckCollision(x, y);
    }
}



void TextureGenEngine::GUIManager::Drag(double x, double y)
{
    if (m_draggableElement != nullptr)
    {
        m_draggableElement->Drag(x, y);
    }
}

void TextureGenEngine::GUIManager::GetDraggable(int x, int y)
{
    BaseElement* temp;
    for (BaseElement *child : m_children)
    {
        temp = child->GetDraggable(x, y);
        if (temp != nullptr)
        {
            m_draggableElement = temp;
            LOG_DEBUG("Draggable element found\n");
            break;
        }
    }
}

void TextureGenEngine::GUIManager::RemoveDraggable()
{
    m_draggableElement = nullptr;
}

void TextureGenEngine::GUIManager::Resize(int width, int height)
{
    for (BaseElement *child : m_children)
    {
        child->Resize(width, height, m_width, m_height);
    }
    m_width = width;
    m_height = height;
}

void TextureGenEngine::GUIManager::AddChild(BaseElement* element)
{
    m_children.push_back(element);
}
