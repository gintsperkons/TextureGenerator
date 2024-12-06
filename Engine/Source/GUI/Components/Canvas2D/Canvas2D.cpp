#include "Canvas2D.h"
#include "GUI/GUIManager.h"
#include "Core/Renderer/Mesh.h"
#include "GUI/Components/MenuComponent/MenuComponent.h"

TextureGenEngine::Canvas2D::Canvas2D(int x, int y, int width, int height, ScalingType xScaling, ScalingType yScaling) : Panel(x, y, width, height, xScaling, yScaling)
{
}

void TextureGenEngine::Canvas2D::Draw()
{
    m_manager->Scissors(m_x, m_y+MenuComponent::height, m_width, m_height);
    m_background->Draw();   
    m_manager->ScissorsReset();
}

TextureGenEngine::Canvas2D::~Canvas2D()
{
}
