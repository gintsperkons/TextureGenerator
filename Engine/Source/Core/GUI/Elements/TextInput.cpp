#include "TextInput.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Renderer/Mesh.h"
#include "Core/GUI/SubElements/TextElement.h"
#include "Core/GUI/Structures.h"

TextureGenEngine::TextInput::TextInput(int x, int y, int width, int height)
    : BaseElement(x, y, width, height)
{
    m_mesh = ObjectFactory::CreateSquare(width, height);
    m_mesh->SetPosition(x, y);
    m_mesh->ChangeColor(0.1f, 0.1f, 0.1f, 1.0f);
    m_text = new TextElement();
    m_selectable = true;
    m_writable = true;
}

TextureGenEngine::TextInput::~TextInput()
{
}

void TextureGenEngine::TextInput::Draw()
{
    m_mesh->Draw();
    m_text->Draw(m_inputText, m_x, m_y, m_height, m_width, glm::vec3(1.0f, 1.0f, 1.0f), AlignmentHorizontal::LEFT, AlignmentVertical::CENTER);
}
