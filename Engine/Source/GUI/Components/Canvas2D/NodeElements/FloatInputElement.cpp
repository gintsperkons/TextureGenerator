#include "FloatInputElement.h"
#include "InputConnector.h"
#include "GUI/Components/TextInput.h"

TextureGenEngine::FloatInputElement::FloatInputElement()
{

    m_x = 0;
    m_y = 100;
    m_width = 140;
    m_height = 20;

    m_draggable = false;
    m_type = "FloatInputElement";
    m_dataType = NodeDataTypes::FLOAT;
    m_inputImage->SetDataType(m_dataType);
    m_textInput->SetAllowCharacters("0123456789.");
    m_textInput->SetFilterState(true);
    m_textInput->SetInputType(TextInputType::FLOAT);
    m_textInput->SetOnFloatChange([&](float data)
                                  { 
            
            if (m_onDataChange)
            {
                m_onDataChange();
            } });
}

void TextureGenEngine::FloatInputElement::SetData(float data)
{
    m_textInput->SetFloat(data);
}

void TextureGenEngine::FloatInputElement::GetData(float &data)
{
    m_textInput->GetFloat(data);
}

void TextureGenEngine::FloatInputElement::UpdateData(float data)
{
    m_textInput->SetFloat(data);
}

std::string TextureGenEngine::FloatInputElement::ExportElementData()
{
    float data;
    m_textInput->GetFloat(data);
    return std::to_string(data);
}

void TextureGenEngine::FloatInputElement::ImportElementData(std::string data)
{
    m_textInput->SetFloat(std::stof(data));
}

TextureGenEngine::FloatInputElement::~FloatInputElement()
{
}
