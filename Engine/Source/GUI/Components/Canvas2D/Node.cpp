#include "Node.h"

TextureGenEngine::Node::Node(int x, int y, int width, int height):
Component(x, y, width, height)
{
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

TextureGenEngine::Node::~Node()
{
}
