#include "TextualInputElement.h"
#include "Core/Logger/Logger.h"
#include "GUI/Components/TextInput.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Renderer/Mesh.h"
#include "NodeTypes.h"
#include "InputConnector.h"
#include "OutputConnector.h"

TextureGenEngine::TextualInputElement::TextualInputElement()
    :
NodeElement()
{
    m_nodeType = ElementType::TEXT;
    m_x = 0;
    m_y = 100;
    m_width = 140;
    m_height = 20;
    
    m_draggable = false;
    m_type = "TextualInputElement";

    m_textInput = new TextInput(0, 200, 200, 20);
    m_textInput->SetParent(this);
    m_textInput->SetBackground(Color(1.0f, 1.0f, 1.0f, 0.1f));
    m_dataType = NodeDataTypes::TEXT;
    m_inputImage->SetDataType(m_dataType);
    if (typeid(*this) == typeid(TextualInputElement)) {
        m_textInput->SetOnTextChange([&](std::string text){ 
            if (m_onDataChange)
            {
                m_onDataChange();
            }
        });
    }
}

void TextureGenEngine::TextualInputElement::Draw()
{
    m_textInput->Draw();
    m_inputImage->Draw();
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

void TextureGenEngine::TextualInputElement::LockInput()
{
    LOG_DEBUG("Locking input\n");
    m_textInput->Disable();
}

void TextureGenEngine::TextualInputElement::UnlockInput()
{
    m_textInput->Enable();
}

void TextureGenEngine::TextualInputElement::GetData(std::string &data)
{
    if (m_textInput)
    {
        m_textInput->GetText(data);
    }
}

void TextureGenEngine::TextualInputElement::UpdateData(std::string data)
{
    if (m_textInput)
    {
        m_textInput->SetText(data);
    }
}

std::string TextureGenEngine::TextualInputElement::ExportElementData()
{
    std::string data = "";
    if (m_textInput)
    {
        m_textInput->GetText(data);
    }
    if (data == "" || data == "-=-" || data == " ")
    {
        data = "-=-";
    }
    return data;
}

void TextureGenEngine::TextualInputElement::ImportElementData(std::string data)
{
    if (data == "-=-")
    {
        return;
    }
    if (m_textInput)
    {
        m_textInput->SetText(data);
    }
}

TextureGenEngine::TextualInputElement::~TextualInputElement()
{
    if (m_textInput != nullptr)
        delete m_textInput;
    m_textInput = nullptr;
}
