#include "Node.h"
#include "Core/Renderer/Mesh.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Logger/Logger.h"
#include "GUI/GUIManager.h"
#include "Core/Window/Window.h"
#include "NodeElements/NodeElement.h"
#include "NodeElements/InputConnector.h"
#include "NodeElements/OutputConnector.h"
#include "Canvas2D.h"

TextureGenEngine::Node::Node(float x, float y):
Component(x, y, 100, c_titleHeight)
{
    m_dataBackground = ObjectFactory::CreateSquare(100, 100);
    m_draggable = true;
    m_selectable = true;
    m_type = "Node";
}

void TextureGenEngine::Node::Init(float width, float height)
{
    if (m_parent)
    {
        m_x = m_parent->GetX() + m_x;
        m_y = m_parent->GetY() + m_y;
        m_dataBackground->SetPosition(m_x, m_y - m_dataBackgroundHeight);
    }
    Component::Init(width, height);
    for (auto &element : m_elements)
    {
        element->Init(width, height);
    }
}

void TextureGenEngine::Node::Draw()
{
    Component::Draw();
    m_dataBackground->Draw();
    for (auto &element : m_elements)
    {
        element->Draw();
    }
}

void TextureGenEngine::Node::AddElement(NodeElement *element)
{
    element->SetParent(this);
    element->SetManager(m_manager); 
    element->Setup(m_x, m_y);
    element->SetNode(this);
    m_elements.push_back(element);
    float maxWidth = 0;
    float totalHeight = 10;
    for (auto &element : m_elements)
    {
        if (element->GetWidth() > maxWidth)
        {
            maxWidth = element->GetWidth();
        }
        totalHeight += element->GetHeight();
    }
    LOG_DEBUG("Max width %f\n", maxWidth);
    LOG_DEBUG("Total height %f\n", totalHeight);
    m_scales[0] = maxWidth/m_width;
    m_scales[1] = totalHeight / m_dataBackgroundHeight;
    LOG_DEBUG("Scales %f %f\n", m_scales[0], m_scales[1]);
    LOG_DEBUG("total height %f, height %f\n", totalHeight, m_height);
    // m_dataBackground->Scale(m_scales[0], m_scales[1]);
    m_dataBackground->SetSize(maxWidth, totalHeight);

    m_dataBackground->SetPosition(m_x, m_y-totalHeight);
    m_background->Scale(m_scales[0], 1);
    m_width = maxWidth;
    m_dataBackgroundHeight = totalHeight;
}

void TextureGenEngine::Node::OnMouseDrag(float x, float y)
{
    Component::OnMouseDrag(x, y);
    m_dataBackground->Move(x,y);
    for (auto &element : m_elements)
    {
        element->OnMouseDrag(x, y);
    }
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

    if (testX > x1 && testX < x2 && testY > y1 && testY < y2)
    {
        return true;
    }
    return false;
}

float TextureGenEngine::Node::GetOffset(NodeElement *element)
{
    float offset = c_titleHeight;
    return offset;
}

TextureGenEngine::Component *TextureGenEngine::Node::SelectObject(float x, float y)
{
    for (auto &element : m_elements)
    {
        if (element->CheckCollision(x, y))
        {
            LOG_DEBUG("Selecting element\n");
            Component* subElement = element->SelectObject(x, y);
            if (subElement)
            {
                return subElement;
            }
        }
    }
    if (m_selectable && CheckCollision(x, y))
    {
        return this;
    }
    return nullptr;
}

TextureGenEngine::Node::~Node()
{
    if (m_dataBackground)
    {
        delete m_dataBackground;
    }
    for (auto &element : m_elements)
    {
        delete element;
    }
    if (m_parent)
    {
        m_parent->RemoveChild(this);
    }
}

TextureGenEngine::InputConnector *TextureGenEngine::Node::GetInputConnector(float x, float y)
{
    for (auto &element : m_elements)
    {
        InputConnector *input = element->GetInputConnector(x, y);
        if (input)
        {
            return input;
        }
    }
    return nullptr;
}

TextureGenEngine::OutputConnector *TextureGenEngine::Node::GetOutputConnector(float x, float y)
{
    for (auto &element : m_elements)
    {
        OutputConnector *output = element->GetOutputConnector(x, y);
        if (output)
        {
            return output;
        }
    }
    return nullptr;
}

TextureGenEngine::Canvas2D *TextureGenEngine::Node::GetCanvas()
{
    return dynamic_cast<Canvas2D *>(m_parent);
}
