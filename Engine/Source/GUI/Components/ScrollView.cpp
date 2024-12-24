#include "ScrollView.h"

TextureGenEngine::ScrollView::ScrollView(float x, float y, float width, float height, ScalingType xScaling, ScalingType yScaling)
    : Panel(x, y, width, height, xScaling, yScaling)
{
    m_draggable = true;
    m_selectable = true;
    m_type = "ScrollView";
}

void TextureGenEngine::ScrollView::Draw()
{
    Panel::Draw();
}

TextureGenEngine::ScrollView::~ScrollView()
{
}
