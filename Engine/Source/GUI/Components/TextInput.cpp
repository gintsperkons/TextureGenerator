#include "TextInput.h"
#include "Core/Renderer/Text.h"
#include "Core/Renderer/Structures/Aligment.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Logger/Logger.h"
#include "Core/Renderer/Mesh.h"
#include "GUI/GUIManager.h"

void TextureGenEngine::TextInput::CheckCursorInView()
{
}

TextureGenEngine::TextInput::TextInput(int x, int y, int width, int height) : Component(x, y, width, height)
{
    m_textMesh = new Text();
    m_cursor = ObjectFactory::CreateSquare(4, height);
    m_cursor->ChangeColor(0, 0, 0, 1);
    m_cursor->SetPosition(x, y);
    m_type = "TextInput";
    m_selectable = true;

    m_cursor->ChangeShader("cursor");
}

TextureGenEngine::TextInput::~TextInput()
{
}

void TextureGenEngine::TextInput::Init(int width, int height)
{
    m_x = m_parent->GetX() + m_x;
    m_y = m_parent->GetY() + m_y;
    m_background->SetPosition(m_x, m_y);

    m_width = width;
    m_height = height;
}

void TextureGenEngine::TextInput::Draw()
{
    if (m_manager == nullptr) return;
    m_manager->ScissorsPush(m_x, m_y, m_width, m_height);
    Component::Draw();
    if ((m_cursor && m_textMesh && m_showCursor))
    {
        m_cursor->Draw();
    }
    if (m_textMesh)
    {
        LOG_DEBUG("position %f %f\n", m_x + m_textDrawOffset, m_y);
        m_textMesh->Draw(m_text, m_x + m_textDrawOffset, m_y, m_height, m_width, 12, glm::vec3(0, 0, 0), AlignmentHorizontal::LEFT, AlignmentVertical::CENTER);
    }
    m_manager->ScissorsPop();
}

void TextureGenEngine::TextInput::AddChar(unsigned int codepoint)
{
    m_text.insert(m_cursorPosition, 1, static_cast<char>(codepoint));
    m_cursorPosition++;

    float textBeforeSize = m_textMesh->GetTextWidth(m_text.substr(0, m_cursorPosition), 12);
    if (textBeforeSize > m_width)
    {   LOG_DEBUG("position %f %f\n", m_x, m_y);
    LOG_DEBUG("drawOffset %f\n", m_textDrawOffset);
    m_textDrawOffset = m_width - 5 - textBeforeSize;
    m_cursor->SetPosition(m_x + m_width - 5, m_y);
    return;
    }
    m_cursor->SetPosition(m_x + textBeforeSize, m_y);
}

void TextureGenEngine::TextInput::RemoveCharBefore()
{
    if (m_text.length() > 0 && m_cursorPosition > 0)
    {
        m_text.erase(m_cursorPosition - 1, 1);
        m_cursorPosition--;
        float textBeforeSize = m_textMesh->GetTextWidth(m_text.substr(0, m_cursorPosition), 12);
        if (textBeforeSize > m_width)
        {
            m_textDrawOffset = m_width - 5 - textBeforeSize;
            return;
        }
        if (m_textDrawOffset != 0)
            m_textDrawOffset = 0;
        m_cursor->SetPosition(m_x + m_textMesh->GetTextWidth(m_text.substr(0, m_cursorPosition), 12), m_y);
    }
}

void TextureGenEngine::TextInput::RemoveCharAfter()
{
    if (m_cursorPosition < m_text.length())
    {
        m_text.erase(m_cursorPosition, 1);
        float textBeforeSize = m_textMesh->GetTextWidth(m_text.substr(0, m_cursorPosition), 12);
        if (textBeforeSize > m_width)
        {
            m_textDrawOffset = m_x - textBeforeSize + m_width - 5;
            return;
        }
        m_cursor->SetPosition(m_x + m_textMesh->GetTextWidth(m_text.substr(0, m_cursorPosition), 12), m_y);
    }
}

void TextureGenEngine::TextInput::MoveCursorLeft()
{
    if (m_cursorPosition > 0)
    {
        m_cursorPosition--;
        float textBeforeSize = m_textMesh->GetTextWidth(m_text.substr(0, m_cursorPosition), 12);
        if (textBeforeSize > m_width)
        {
            m_textDrawOffset = m_x - textBeforeSize + m_width - 5;
            m_cursor->SetPosition(m_x + m_width - 5, m_y);
            return;
        }

        if (m_textDrawOffset != 0)
            m_textDrawOffset = 0;
        m_cursor->SetPosition(m_x + textBeforeSize, m_y);
    }
}

void TextureGenEngine::TextInput::MoveCursorRight()
{
    if (m_cursorPosition < m_text.length())
    {
        m_cursorPosition++;
        float textBeforeSize = m_textMesh->GetTextWidth(m_text.substr(0, m_cursorPosition), 12);
        if (textBeforeSize > m_width)
        {
            m_textDrawOffset = m_x - textBeforeSize + m_width - 5;
            m_cursor->SetPosition(m_x + m_width - 5, m_y);
            return;
        }
        m_cursor->SetPosition(m_x + textBeforeSize, m_y);
    }
}

void TextureGenEngine::TextInput::SetPosition(float x, float y)
{
    m_x = x;
    m_y = y;
    m_cursor->SetPosition(x, y);
    m_background->SetPosition(x, y);
    m_textMesh->Draw(m_text, m_x, m_y, m_height, m_width, 12, glm::vec3(0, 0, 0), AlignmentHorizontal::LEFT, AlignmentVertical::CENTER);
}
