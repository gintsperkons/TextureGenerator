#include "IntegerElement.h"
#include "GUI/Components/TextInput.h"
#include "InputConnector.h"

TextureGenEngine::IntegerElement::IntegerElement()
    : TextualInputElement()
{
    m_draggable = false;
    m_type = "IntegerElement";
    m_x = 0;
    m_y = 100;
    m_width = 140;
    m_height = 20;

    m_dataType = NodeDataTypes::INTEGER;
    m_inputImage->SetDataType(m_dataType);
    m_textInput->SetAllowCharacters("0123456789");
    m_textInput->SetFilterState(true);
    m_textInput->SetInputType(TextInputType::INTEGER);
    m_textInput->SetOnIntegerChange([&](int data)
                                  { 
            
            if (m_onDataChange)
            {
                m_onDataChange();
            } });
}
void TextureGenEngine::IntegerElement::SetData(int data)
{
    m_textInput->SetInteger(data);
}
void TextureGenEngine::IntegerElement::GetData(int &data)
{
    m_textInput->GetInteger(data);
}
void TextureGenEngine::IntegerElement::UpdateData(int data)
{
    m_textInput->SetInteger(data);
}
TextureGenEngine::IntegerElement::~IntegerElement()
{
}