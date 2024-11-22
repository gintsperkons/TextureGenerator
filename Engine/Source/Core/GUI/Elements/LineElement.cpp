#include "LineElement.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Renderer/Line.h"

TextureGenEngine::LineElement::LineElement(int xStart, int yStart, int xEnd, int yEnd) : BaseElement(0, 0, 0, 0)
{
    m_line = ObjectFactory::CreateLine(xStart, yStart, xEnd, yEnd);
}

void TextureGenEngine::LineElement::Draw()
{
    if (m_line != nullptr)
        m_line->Draw();
}

void TextureGenEngine::LineElement::UpdatePositionRelativeToParent(float x, float y)
{
    m_x += x;
    m_y += y;

    //m_line->SetPosition(m_x, m_y);
}

TextureGenEngine::LineElement::~LineElement()
{
}
