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
}

TextureGenEngine::NodeElement::~NodeElement()
{
    if (m_inputImage != nullptr)
        delete m_inputImage;
    m_inputImage = nullptr;
}

void TextureGenEngine::NodeElement::OnMouseDrag(float x, float y)
{
    m_x += x;
    m_y -= y;
    if (m_inputImage) m_inputImage->Move(x, y);
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
}

TextureGenEngine::Component *TextureGenEngine::NodeElement::SelectObject(float x, float y)
{
    if (m_inputImage->CheckCollision(x, y))
    {
        return m_inputImage;
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
    return nullptr;
}

std::string TextureGenEngine::NodeElement::GetConnectedOutputs()
{
    return m_inputImage->GetConnectionUUID();
}

void TextureGenEngine::NodeElement::SetOnDataChange(std::function<void()> onDataChange)
{
    m_onDataChange = onDataChange;
}

void TextureGenEngine::NodeElement::TriggerDataChange()
{
    if (m_onDataChange)
    {
        m_onDataChange();
    }
}
