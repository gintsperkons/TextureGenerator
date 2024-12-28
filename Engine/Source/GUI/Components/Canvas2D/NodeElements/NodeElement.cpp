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
    m_inputImage->SetManager(m_manager);
    m_inputImage->SetParent(this);
    m_outputImage = new OutputConnector();
    m_outputImage->SetManager(m_manager);
    m_outputImage->SetParent(this);
}

TextureGenEngine::NodeElement::~NodeElement()
{
}

void TextureGenEngine::NodeElement::OnMouseDrag(float x, float y)
{
    m_x += x;
    m_y -= y;
    m_inputImage->Move(x, y);
    m_outputImage->Move(x, y);
}

void TextureGenEngine::NodeElement::Setup(float x, float y)
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

void TextureGenEngine::NodeElement::SetManager(GUIManager *manager)
{
    m_manager = manager;
    m_inputImage->SetManager(manager);
    m_outputImage->SetManager(manager);
}

TextureGenEngine::Component *TextureGenEngine::NodeElement::SelectObject(float x, float y)
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

TextureGenEngine::InputConnector *TextureGenEngine::NodeElement::GetInputConnector(float x, float y)
{
    if (m_inputImage->CheckCollision(x, y))
    {
        return m_inputImage;
    }
    return nullptr;
}

TextureGenEngine::OutputConnector *TextureGenEngine::NodeElement::GetOutputConnector(float x, float y)
{
    if (m_outputImage->CheckCollision(x, y))
    {
        return m_outputImage;
    }
    return nullptr;
}
