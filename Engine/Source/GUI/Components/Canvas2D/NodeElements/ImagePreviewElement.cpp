#include "ImagePreviewElement.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Renderer/TextureData.h"
#include "Core/Renderer/Texture.h"
#include "Core/Logger/Logger.h"

#include "FastNoise/FastNoise.h"
#include "FastSIMD/FastSIMD.h"

#include <random>
#include <iostream>

TextureGenEngine::ImagePreviewElement::ImagePreviewElement()
: NodeElement()
{
    m_nodeType = ElementType::IMAGE_PREVIEW;
    m_x = 0;
    m_y = 0;
    m_width = 100;
    m_height = 100;
    m_imageSize[0] = 100;
    m_imageSize[1] = 100;

    m_texture = new TextureGenEngine::Texture();
    m_textureData = new TextureData(m_imageSize[0], m_imageSize[1]);
    m_imageData.resize(m_imageSize[0] * m_imageSize[1]);
    m_texture->LoadTexture(m_textureData);
    m_background->ChangeTexture(m_texture);
}

TextureGenEngine::ImagePreviewElement::~ImagePreviewElement()
{
    delete m_textureData;
    m_textureData = nullptr;
    delete m_texture;
    m_texture = nullptr;
}

void TextureGenEngine::ImagePreviewElement::OnMouseDrag(float x, float y)
{
    NodeElement::OnMouseDrag(x, y);
    m_background->Move(x, y);
}

void TextureGenEngine::ImagePreviewElement::Setup(float x, float y)
{
    NodeElement::Setup(x + 20, y - m_height + 20);
    m_background->SetPosition(m_x, m_y);
    LOG_DEBUG("Setting up ImagePreviewElement\n");
    LOG_DEBUG("position %f %f\n", m_x, m_y);
}

void TextureGenEngine::ImagePreviewElement::Draw()
{
    NodeElement::Draw();
    if (m_needsUpdate)
    {
        UpdateImageBuffer();
        m_needsUpdate = false;
    }
}

TAPI void TextureGenEngine::ImagePreviewElement::SetImageSize(int width, int height)
{
    LOG_DEBUG("Setting image size %d %d\n", width, height);
    m_imageSize[0] = width;
    m_imageSize[1] = height;
    m_textureData->SetSize(m_imageSize[0], m_imageSize[1]);
    m_imageData.resize(m_imageSize[0] * m_imageSize[1]);
    m_texture->UpdateTexture(m_textureData);
}

void TextureGenEngine::ImagePreviewElement::UpdateImageBuffer()
{
    LOG_DEBUG("Updating image\n");
    LOG_DEBUG("Width %d Height %d\n", m_imageSize[0], m_imageSize[1]);
    LOG_DEBUG("Data size %d\n", m_imageData.size());
    for (int i = 0; i < m_imageSize[0]; i++)
    {
        for (int j = 0; j < m_imageSize[1]; j++)
        {
            if (i * m_imageSize[0] + j < m_imageData.size())
            {
                int color = static_cast<int>((m_imageData[i * m_imageSize[0] + j] + 1) * 127.5);
                m_textureData->UpdatePixel(i, j, color, color, color, 255);
            }
        }
    }
    m_texture->UpdateTexture(m_textureData);
}

void TextureGenEngine::ImagePreviewElement::UpdateImage()
{   
    m_needsUpdate = true;
}

unsigned char* TextureGenEngine::ImagePreviewElement::GetCharData()
{
    return m_textureData->GetRawData();
}