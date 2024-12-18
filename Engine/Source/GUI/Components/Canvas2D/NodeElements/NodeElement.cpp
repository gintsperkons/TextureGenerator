#include "NodeElement.h"
#include "GUI/Components/Canvas2D/Node.h"
#include "OutputConnector.h"
#include "InputConnector.h"
#include <Core/Logger/Logger.h>

TextureGenEngine::NodeElement::NodeElement() : Component(0, 0, 100, 100)
{
    m_draggable = false;
    m_type = "NodeElement";
    m_elementType = "base";
    m_inputImage = new InputConnector();
    m_outputImage = new OutputConnector();
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
    Node *parent = dynamic_cast<Node *>(m_parent);
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

TextureGenEngine::Component *TextureGenEngine::NodeElement::SelectObject(double x, double y)
{
    LOG_DEBUG("Selecting object----\n");
    LOG_DEBUG("x %f y %f\n", x, y);
    LOG_DEBUG("output x %f y %f\n", m_outputImage->GetX(), m_outputImage->GetY());
    LOG_DEBUG("output width %f height %f\n", m_outputImage->GetWidth(), m_outputImage->GetHeight());
    if (m_inputImage->CheckCollision(x, y))
    {
        return m_inputImage;
    }
    if (m_outputImage->CheckCollision(x, y))
    {
        LOG_DEBUG("Selecting output\n");
        return m_outputImage;
    }
    return nullptr;
}