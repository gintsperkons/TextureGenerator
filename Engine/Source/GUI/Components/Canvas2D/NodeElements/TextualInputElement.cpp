#include "TextualInputElement.h"
#include "Core/Logger/Logger.h"
#include "GUI/Components/TextInput.h"

TextureGenEngine::TextualInputElement::TextualInputElement()
    :
NodeElement()
{
    m_x = 0;
    m_y = 100;
    m_draggable = false;
    m_type = "TextualInputElement";
    m_textInput = new TextInput(0,200, 100, 20);
    m_textInput->SetParent(this);
    m_textInput->SetBackground(Color(0.0f, 1.0f, 1.0f, 1.0f));
}

void TextureGenEngine::TextualInputElement::Draw()
{
    m_textInput->Draw();
}

void TextureGenEngine::TextualInputElement::SetManager(GUIManager *manager)
{
    m_manager = manager;
    LOG_DEBUG("Setting manager for TextualInputElement%d\n", m_manager);
    m_textInput->SetManager(manager);
}

void TextureGenEngine::TextualInputElement::Init(int width, int height)
{
    m_width = width;
    m_height = height;
    m_textInput->Init(width, height);
}

void TextureGenEngine::TextualInputElement::Setup(int x, int y)
{
    NodeElement::Setup(x, y);
    LOG_DEBUG("Setting up TextualInputElement\n");
    LOG_DEBUG("position %f %f\n", m_x, m_y);
    m_textInput->SetPosition(m_x, m_y);
}

void TextureGenEngine::TextualInputElement::OnMouseDrag(double x, double y)
{
    NodeElement::OnMouseDrag(x, y);
    m_textInput->SetPosition(m_x, m_y);
}

TextureGenEngine::Component *TextureGenEngine::TextualInputElement::SelectObject(double x, double y)
{
     if (m_textInput->CheckCollision(x, y))
    {
        return m_textInput;
    }
    return nullptr;
}

TextureGenEngine::TextualInputElement::~TextualInputElement()
{
}
