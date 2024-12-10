#include "TextInput.h"
#include "Core/Renderer/Text.h"
#include "Core/Renderer/Structures/Aligment.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Logger/Logger.h"
#include "Core/Renderer/Mesh.h"
#include "GUI/GUIManager.h"

TextureGenEngine::TextInput::TextInput(int x, int y, int width, int height):
Component(x, y, width, height)
{
    m_textMesh = new Text();
    m_cursor = ObjectFactory::CreateSquare(4, height);
    m_cursor->ChangeColor(0,0,0,1);
    m_cursor->SetPosition(x, y);
    m_type = "TextInput";
    m_selectable = true;
}

TextureGenEngine::TextInput::~TextInput()
{
}

void TextureGenEngine::TextInput::Draw()
{
    Component::Draw();
    if ((m_cursor && m_textMesh && m_showCursor))
    {   
        m_cursor->Draw();
    }
    if (m_textMesh)
    {  
        m_textMesh->Draw(m_text, m_x, m_y, m_height, m_width, 12, glm::vec3(0, 0, 0), AlignmentHorizontal::LEFT, AlignmentVertical::CENTER);
    }
}

void TextureGenEngine::TextInput::AddChar(unsigned int codepoint)
{
    m_text.append(1, static_cast<char>(codepoint));
    m_cursor->SetPosition(m_x + m_textMesh->GetTextWidth(m_text, 12), m_y);
    
}

void TextureGenEngine::TextInput::RemoveChar()
{
    if (m_text.length() > 0)
    {
        m_text.pop_back();
        m_cursor->SetPosition(m_x + m_textMesh->GetTextWidth(m_text, 12), m_y);
    }
}
