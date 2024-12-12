#include "Canvas2D.h"
#include "GUI/GUIManager.h"
#include "GUI/Components/MenuComponent/MenuComponent.h"
#include "Core/Logger/Logger.h"
#include "Node.h"

TextureGenEngine::Canvas2D::Canvas2D(int x, int y, int width, int height, ScalingType xScaling, ScalingType yScaling) : Panel(x, y, width, height, xScaling, yScaling)

{
    m_draggable = true;
    m_selectable = true;
    m_type = "Canvas2D";
}

void TextureGenEngine::Canvas2D::Draw()
{
    float oldWidth, oldHeight;
    m_manager->GetOldSize(oldWidth, oldHeight);
    m_manager->Scissors(m_x, m_y, m_width, m_height);
    Panel::Draw();
    
    for (auto &node : m_nodes)
    {
        node->Draw();
    }
    m_manager->ScissorsReset();
}

TextureGenEngine::Canvas2D::~Canvas2D()
{
}

void TextureGenEngine::Canvas2D::AddNode(Node *node)
{
    m_nodes.push_back(node);
    node->SetParent(this);
    node->SetManager(m_manager);
    node->Init(m_width, m_height);
}

TextureGenEngine::Component *TextureGenEngine::Canvas2D::SelectObject(double x, double y)
{
    for (auto &node : m_nodes)
    {
        if (node->CheckCollision(x, y) && node->IsSelectable())
        {
            return node;
        }
    }
    if (m_selectable)
    {
        return this;
    }
    return nullptr;
}

void TextureGenEngine::Canvas2D::OnMouseDrag(double x, double y)
{
    for (auto &node : m_nodes)
    {
        node->OnMouseDrag(x, y);
    }
}
