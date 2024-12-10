#include "TextInput.h"
#include "Core/Renderer/Text.h"
#include "Core/Renderer/Structures/Aligment.h"
#include "Core/Logger/Logger.h"

TextureGenEngine::TextInput::TextInput(int x, int y, int width, int height):
Component(x, y, width, height)
{
    m_textMesh = new Text();
    m_type = "TextInput";
    m_selectable = true;
}

TextureGenEngine::TextInput::~TextInput()
{
}

void TextureGenEngine::TextInput::Draw()
{
    Component::Draw();
    if (m_textMesh)
    {
        m_textMesh->Draw(m_text, m_x, m_y, m_height, m_width, 12, glm::vec3(0, 0, 0), AlignmentHorizontal::LEFT, AlignmentVertical::CENTER);
    }
}

void TextureGenEngine::TextInput::AddChar(unsigned int codepoint)
{
    m_text.append(1, static_cast<char>(codepoint));
    
}

void TextureGenEngine::TextInput::RemoveChar()
{
    if (m_text.length() > 0)
    {
        m_text.pop_back();
    }
}
