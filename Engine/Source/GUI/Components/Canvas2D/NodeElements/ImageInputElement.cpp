#include "ImageInputElement.h"
#include "InputConnector.h"

TextureGenEngine::ImageInputElement::ImageInputElement()
{
    m_nodeType = ElementType::IMAGE_INPUT;
    m_x = 0;
    m_y = 0;
    m_width = 100;
    m_height = 20;
    m_dataType = NodeDataTypes::PATTERNGENERATOR;
    m_inputImage->SetDataType(m_dataType);
}

TextureGenEngine::ImageInputElement::~ImageInputElement()
{
}

void TextureGenEngine::ImageInputElement::Draw()
{
    m_inputImage->Draw();
}

void TextureGenEngine::ImageInputElement::Init(float width, float height)
{
    m_width = width;
    m_height = height;
}

void TextureGenEngine::ImageInputElement::Setup(float x, float y)
{
    NodeElement::Setup(x, y);
    m_inputImage->SetPosition(m_x, m_y);
}

void TextureGenEngine::ImageInputElement::OnMouseDrag(float x, float y)
{
    NodeElement::OnMouseDrag(x, y);
}

void TextureGenEngine::ImageInputElement::UpdateData(std::vector<PatternGeneratorData> data)
{
    m_imageGenerationSequence = data;
    if (m_onDataChange)
    {
        m_onDataChange();
    }
}
