#include "ScrollView.h"

TextureGenEngine::ScrollView::ScrollView(int x, int y, int width, int height, ScalingType xScaling, ScalingType yScaling)
    : Panel(x, y, width, height, xScaling, yScaling)
{
    m_draggable = true;
    m_selectable = true;
    m_type = "ScrollView";
}

void TextureGenEngine::ScrollView::Draw()
{
    ScrollView::Draw();
}

TextureGenEngine::ScrollView::~ScrollView()
{
}
