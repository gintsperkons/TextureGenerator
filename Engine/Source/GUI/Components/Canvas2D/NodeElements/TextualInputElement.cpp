#include "TextualInputElement.h"
#include "Core/Logger/Logger.h"
#include "GUI/Components/TextInput.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Renderer/Mesh.h"
#include "InputConnector.h"
#include "OutputConnector.h"

TextureGenEngine::TextualInputElement::TextualInputElement()
    :
NodeElement()
{
    m_x = 0;
    m_y = 100;
    m_width = 140;
    m_height = 20;
    
    m_draggable = false;
    m_type = "TextualInputElement";
    m_textInput = new TextInput(0,200, 100, 20);
    m_textInput->SetParent(this);
    m_textInput->SetBackground(Color(0.0f, 1.0f, 1.0f, 1.0f));
    m_dataType = "text";
    m_inputImage->SetType(m_dataType);
    m_outputImage->SetType(m_dataType);
}

void TextureGenEngine::TextualInputElement::Draw()
{
    m_textInput->Draw();
    m_inputImage->Draw();
    m_outputImage->Draw();
}

void TextureGenEngine::TextualInputElement::SetManager(GUIManager *manager)
{
    NodeElement::SetManager(manager);
    m_manager = manager;
    LOG_DEBUG("Setting manager for TextualInputElement%d\n", m_manager);
    m_textInput->SetManager(manager);
}

void TextureGenEngine::TextualInputElement::Init(float width, float height)
{
    m_width = width;
    m_height = height;
    m_textInput->Init(width, height);
}

void TextureGenEngine::TextualInputElement::Setup(float x, float y)
{
    NodeElement::Setup(x, y);
    LOG_DEBUG("Setting up TextualInputElement\n");
    LOG_DEBUG("position %f %f\n", m_x, m_y);
    m_textInput->SetPosition(m_x+20, m_y);
    m_inputImage->SetPosition(m_x, m_y);
    m_outputImage->SetPosition(m_x+120, m_y);
}

void TextureGenEngine::TextualInputElement::OnMouseDrag(float x, float y)
{
    NodeElement::OnMouseDrag(x, y);
    m_textInput->Move(x, y);
}

TextureGenEngine::Component *TextureGenEngine::TextualInputElement::SelectObject(float x, float y)
{
    Component* element = NodeElement::SelectObject(x, y);
    if (element) return element;
     if (m_textInput->CheckCollision(x, y))
    {
        return m_textInput;
    }
    return nullptr;
}

TextureGenEngine::TextualInputElement::~TextualInputElement()
{
}
