#include "Label.h"
#include "Core/Renderer/Text.h"

TextureGenEngine::Label::Label(int x, int y, int width, int height, const std::string &text)
: Component(x,y,width,height), m_text(new Text())
{
}

TextureGenEngine::Label::~Label()
{
}

void TextureGenEngine::Label::Draw()
{
    Component::Draw();
    if (m_text) m_text->Draw("test", m_x,m_y,m_height,m_width,12, glm::vec3(0.0f, 1.0f, 0.0f), AlignmentHorizontal::LEFT, AlignmentVertical::TOP);
}
