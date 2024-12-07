#include "Node.h"
#include "Core/Logger/Logger.h"
#include "GUI/GUIManager.h"
#include "Core/Window/Window.h"

TextureGenEngine::Node::Node(int x, int y, int width, int height):
Component(x, y, width, height)
{
    m_draggable = true;
    m_type = "Node";
}

void TextureGenEngine::Node::Init(int width, int height)
{
    if (m_parent)
    {
        m_x = m_parent->GetX() + m_x;
        m_y = m_parent->GetY() + m_y;
    }
    Component::Init(width, height);
}

bool TextureGenEngine::Node::CheckCollision(float x, float y)
{
    float x1 = m_x;
    float x2 = m_x + m_width;
    float y1 = m_y;
    float y2 = m_y + m_height;
    float testX = x;
    float testY = y;


float oldWidth, oldHeight;
m_manager->GetOldSize(oldWidth, oldHeight);
LOG_DEBUG("Old Width: %f Old Height: %f\n", oldWidth, oldHeight);
    
LOG_DEBUG("x1: %f, x2: %f, y1: %f, y2: %f\n", x1, x2, y1, y2);
LOG_DEBUG("testX: %f, testY: %f\n", testX, testY);

    if (testX > x1 && testX < x2 && testY > y1 && testY < y2)
    {
        return true;
    }
    return false;
}

TextureGenEngine::Node::~Node()
{
}
