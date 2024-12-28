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

TextureGenEngine::TextInput::TextInput(float x, float y, float width, float height) : Component(x, y, width, height)
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
    if (m_textMesh)
        delete m_textMesh;
    m_textMesh = nullptr;
    if (m_cursor)
        delete m_cursor;
    m_cursor = nullptr;
}

void TextureGenEngine::TextInput::Init(float width, float height)
{
    m_x = m_parent->GetX() + m_x;
    m_y = m_parent->GetY() + m_y;
    m_background->SetPosition(m_x, m_y);

    m_width = width;
    m_height = height;
}

void TextureGenEngine::TextInput::Draw()
{
    if (m_manager == nullptr)
        return;
    m_manager->ScissorsPush(m_x, m_y, m_width, m_height);
    Component::Draw();
    if ((m_cursor && m_textMesh && m_showCursor))
    {
        m_cursor->Draw();
    }
    if (m_textMesh)
    {
        m_textMesh->Draw(m_text, m_x + m_textDrawOffset, m_y, (int)m_height, (int)m_width, 12, AlignmentHorizontal::LEFT, AlignmentVertical::CENTER);
    }
    m_manager->ScissorsPop();
}

void TextureGenEngine::TextInput::AddChar(unsigned int codepoint)
{
    if (!m_enabled)
        return;
    m_text.insert(m_cursorPosition, 1, static_cast<char>(codepoint));
    m_cursorPosition++;

    float textBeforeSize = m_textMesh->GetTextWidth(m_text.substr(0, m_cursorPosition), 12);
    if (textBeforeSize > m_width)
    {
        m_textDrawOffset = m_width - 5 - textBeforeSize;
        m_cursor->SetPosition(m_x + m_width - 5, m_y);
        return;
    }
    m_cursor->SetPosition(m_x + textBeforeSize, m_y);
    if (m_onTextChange)
        m_onTextChange(m_text);
}

void TextureGenEngine::TextInput::RemoveCharBefore()
{
    if (!m_enabled)
        return;
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

        if (m_onTextChange)
            m_onTextChange(m_text);
    }
}

void TextureGenEngine::TextInput::RemoveCharAfter()
{
    if (!m_enabled)
        return;
    if (m_cursorPosition < m_text.length())
    {
        m_text.erase(m_cursorPosition, 1);
        float textBeforeSize = m_textMesh->GetTextWidth(m_text.substr(0, m_cursorPosition), 12);
        if (textBeforeSize > m_width)
        {
            m_textDrawOffset = m_width - textBeforeSize - 5;
            return;
        }
        m_cursor->SetPosition(m_x + m_textMesh->GetTextWidth(m_text.substr(0, m_cursorPosition), 12), m_y);

        if (m_onTextChange)
            m_onTextChange(m_text);
    }
}

void TextureGenEngine::TextInput::MoveCursorLeft()
{
    if (!m_enabled)
        return;
    if (m_cursorPosition > 0)
    {
        m_cursorPosition--;
        float textBeforeSize = m_textMesh->GetTextWidth(m_text.substr(0, m_cursorPosition), 12);
        if (textBeforeSize > m_width)
        {
            m_textDrawOffset = m_width - textBeforeSize - 5;
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
    if (!m_enabled)
        return;
    if (m_cursorPosition < m_text.length())
    {
        m_cursorPosition++;
        float textBeforeSize = m_textMesh->GetTextWidth(m_text.substr(0, m_cursorPosition), 12);
        if (textBeforeSize > m_width)
        {
            m_textDrawOffset = m_width - textBeforeSize - 5;
            m_cursor->SetPosition(m_x + m_width - 5, m_y);
            return;
        }
        m_cursor->SetPosition(m_x + textBeforeSize, m_y);
    }
}

void TextureGenEngine::TextInput::SetPosition(float x, float y)
{
    Component::SetPosition(x, y);
    m_cursor->SetPosition(x, y);
    m_textMesh->Draw(m_text, m_x, m_y, (int)m_height, (int)m_width, 12, AlignmentHorizontal::LEFT, AlignmentVertical::CENTER);
}

void TextureGenEngine::TextInput::Move(float x, float y)
{
    Component::Move(x, y);
    m_cursor->Move(x, y);
}

void TextureGenEngine::TextInput::Disable()
{
    m_showCursor = false;
    m_enabled = false;
}

void TextureGenEngine::TextInput::Enable()
{
    m_enabled = true;
}
