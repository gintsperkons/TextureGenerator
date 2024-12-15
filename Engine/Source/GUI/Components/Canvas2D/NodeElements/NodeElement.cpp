#include "NodeElement.h"
#include "GUI/Components/Canvas2D/Node.h"

TextureGenEngine::NodeElement::NodeElement():
Component(0, 0, 100, 100)
{
    m_draggable = false;
    m_type = "NodeElement";
    m_elementType = "base";
}

TextureGenEngine::NodeElement::~NodeElement()
{
}

void TextureGenEngine::NodeElement::OnMouseDrag(double x, double y)
{
    m_x += x;
    m_y -= y;

}

void TextureGenEngine::NodeElement::Setup(int x, int y)
{
    Node* parent = dynamic_cast<Node*>(m_parent);
    if (parent)
    {
        m_x = x;
        m_y = y - parent->GetOffset(this);
    }
    else
    {
        m_x = x;
        m_y = y;
    }
}
