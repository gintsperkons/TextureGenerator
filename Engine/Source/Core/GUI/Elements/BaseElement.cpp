#include "BaseElement.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Logger/Logger.h"

void TextureGenEngine::BaseElement::AddChild(BaseElement *child)
{
    child->m_parent = this;
    m_children.push_back(child);
    
}

void TextureGenEngine::BaseElement::Resize(int width, int height, int oldWidth, int oldHeight)
{

    int newX = (int)(((float)m_x / oldWidth) * width);
    int newY = (int)(((float)m_y / oldHeight) * height);

    if (lockY)
        newY = height - m_height;

    if (lockX)
        newX = m_x;

    if (m_mesh != nullptr)
        m_mesh->Move(m_x - newX, m_y - newY);

    float xDiff = ((float)width / (float)oldWidth);
    float yDiff = ((float)height / (float)oldHeight);
    if (lockWidth)
        xDiff = 1;
    if (lockHeight)
        yDiff = 1;

    if (m_mesh != nullptr)
        m_mesh->Scale(xDiff, yDiff);

    m_x = (int)newX;
    m_y = (int)newY;
    for (BaseElement *child : m_children)
    {
        if (child != nullptr)
            child->Resize(width, height, oldWidth, oldHeight);
    }
}