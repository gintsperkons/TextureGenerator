#include "Label.h"
#include "Core/Renderer/Text.h"

TextureGenEngine::Label::Label(float x, float y, float width, float height, const std::string &text)
    : Component(x, y, width, height), m_text(new Text())
{
}

TextureGenEngine::Label::~Label()
{
    if (m_text)
        delete m_text;
    m_text = nullptr;
}

void TextureGenEngine::Label::Draw()
{
    Component::Draw();
    if (m_text)
        m_text->Draw("test", m_x, m_y, (int)m_height, (int)m_width, 12, AlignmentHorizontal::LEFT, AlignmentVertical::TOP);
}
