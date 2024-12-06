#include "Canvas2D.h"
#include "GUI/GUIManager.h"
#include "GUI/Components/MenuComponent/MenuComponent.h"
#include "Node.h"

TextureGenEngine::Canvas2D::Canvas2D(int x, int y, int width, int height, ScalingType xScaling, ScalingType yScaling) : Panel(x, y, width, height, xScaling, yScaling)
{
}

void TextureGenEngine::Canvas2D::Draw()
{
    m_manager->Scissors(m_x, m_y+MenuComponent::height, m_width, m_height);
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
    node->Init(m_width, m_height);
}
