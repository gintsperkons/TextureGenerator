#include "BaseElement.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Logger/Logger.h"

void TextureGenEngine::BaseElement::Resize(int width, int height, int oldWidth, int oldHeight)
{

    int newX = (int)(((float)m_x / oldWidth) * width);
    int newY = (int)(((float)m_y / oldHeight) * height);
    LOG_TRACE("%f %f %f %f\n", (float)m_y / oldHeight, m_y, ((float)m_y / oldHeight) * height, newY);
    LOG_DEBUG("Resizing Element: %d, %d, %d, %d\n", width, height, oldWidth, oldHeight);
    LOG_DEBUG("New Position1: %d, %d Old Position: %d, %d\n", newX, newY, m_x, m_y);
    if(lockY) newY = height-m_height;
    
    if (lockX) newX = m_x;
    LOG_DEBUG("New Position2: %d, %d Old Position: %d, %d\n", newX, newY, m_x, m_y);

    m_mesh->Move(m_x-newX, m_y-newY);

LOG_TRACE("oldWidth: %d, oldHeight: %d, width: %d, height: %d\n", oldWidth, oldHeight, width, height);
    float xDiff = ((float)width/(float)oldWidth);
    float yDiff = ((float)height/(float)oldHeight);
    if (lockWidth) xDiff = 1;
    if (lockHeight) yDiff = 1;
    LOG_DEBUG("Resizing Element 111: %f, %f, %d, %d\n", xDiff, yDiff, width, height);
    m_mesh->Scale(xDiff, yDiff);
    


    m_x = (int)newX;
    m_y = (int)newY;
    LOG_TRACE("New Position3: %d, %d\n", m_x, m_y);
    for (BaseElement *child : m_children)
    {
        child->Resize(width, height, oldWidth, oldHeight);
    }
}