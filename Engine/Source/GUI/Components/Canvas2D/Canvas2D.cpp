#include "Canvas2D.h"
#include "GUI/GUIManager.h"
#include "GUI/Components/MenuComponent/MenuComponent.h"
#include "Core/Logger/Logger.h"
#include "GUI/Components/Canvas2D/NodeElements/InputConnector.h"
#include "GUI/Components/Canvas2D/NodeElements/OutputConnector.h"
#include "Node.h"

TextureGenEngine::Canvas2D::Canvas2D(float x, float y, float width, float height, ScalingType xScaling, ScalingType yScaling) : Panel(x, y, width, height, xScaling, yScaling)

{
    m_draggable = true;
    m_selectable = true;
    m_type = "Canvas2D";
}

void TextureGenEngine::Canvas2D::Draw()
{
    // float x, y;
    //     m_manager->GetMousePosition(x, y);
    //     if (GetInputConnector((float)x, (float)y))
    //     {
    //         LOG_DEBUG("Hand cursor\n");
    //     }
    //     else
    //     {
    //         LOG_DEBUG("Arrow cursor\n");
    //     }
    float oldWidth, oldHeight;
    m_manager->GetOldSize(oldWidth, oldHeight);
    m_manager->ScissorsPush(m_x, m_y, m_width, m_height);
    Panel::Draw();

    for (auto &node : m_nodes)
    {
        node->Draw();
    }
    m_manager->ScissorsPop();
}

TextureGenEngine::Canvas2D::~Canvas2D()
{
    for (auto &node : m_nodes)
    {
        delete node;
    }
    m_nodes.clear();
}

void TextureGenEngine::Canvas2D::AddNode(Node *node)
{
    node->SetParent(this);
    node->SetManager(m_manager);
    m_nodes.push_back(node);
    node->Init(m_width, m_height);
}

TextureGenEngine::Component *TextureGenEngine::Canvas2D::SelectObject(float x, float y)
{
    for (auto &node : m_nodes)
    {
        Component *nodeSubElement = node->SelectObject(x, y);
        if (nodeSubElement)
        {
            return nodeSubElement;
        }
    }
    if (m_selectable)
    {
        return this;
    }
    return nullptr;
}

void TextureGenEngine::Canvas2D::OnMouseDrag(float x, float y)
{
    for (auto &node : m_nodes)
    {
        node->OnMouseDrag(x, y);
    }
}

TextureGenEngine::InputConnector *TextureGenEngine::Canvas2D::GetInputConnector(float x, float y)
{
    for (auto &node : m_nodes)
    {
        InputConnector *inputConnector = node->GetInputConnector(x, y);
        if (inputConnector)
        {
            return inputConnector;
        }
    }
    return nullptr;
}

TextureGenEngine::OutputConnector *TextureGenEngine::Canvas2D::GetOutputConnector(float x, float y)
{
    for (auto &node : m_nodes)
    {
        OutputConnector *outputConnector = node->GetOutputConnector(x, y);
        if (outputConnector)
        {
            return outputConnector;
        }
    }
    return nullptr;
}

void TextureGenEngine::Canvas2D::RemoveChild(Component *child)
{
    for (auto it = m_nodes.begin(); it != m_nodes.end(); ++it)
    {
        if (*it == child)
        {
            m_nodes.erase(it);
            break;
        }
    }
}

void TextureGenEngine::Canvas2D::GetSpawnLocation(float &x, float &y)
{
    m_manager->GetMousePosition(x, y);
    if (x < m_x || x > m_x + m_width || y < m_y || y > m_y + m_height)
    {
        x = m_width / 2;
        y = m_height / 2;
        return;
    }
    x -= m_x;
    y -= m_y;
}

int TextureGenEngine::Canvas2D::GetNodeCount() const
{
    return m_nodes.size();
}

void TextureGenEngine::Canvas2D::GetAllNodes(std::vector<Node *> &nodes)
{
    for (int i = 0; i < m_nodes.size(); i++)
        nodes[i] = m_nodes[i];
}

void TextureGenEngine::Canvas2D::ClearNodes()
{
    for (int i = 0; i < m_nodes.size(); i++)
    {
        delete m_nodes[i];
    }
    m_nodes.clear();
}
