#include "TextElement.h"
#include "Core/Renderer/Text.h"

TextureGenEngine::TextElement::TextElement()
{
    m_text = new Text();
}

void TextureGenEngine::TextElement::Draw(std::string text, float x, float y, int frameHeight, int frameWidth, glm::vec3 color, AlignmentHorizontal hAlign, AlignmentVertical vAlign)
{
    m_text->Draw(text, x, y, frameHeight, frameWidth, textSize, color, hAlign, vAlign);
}

TextureGenEngine::TextElement::~TextElement()
{
    delete m_text;
}
