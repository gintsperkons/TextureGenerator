#include "ImagePreviewElement.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Renderer/TextureData.h"
#include "Core/Renderer/Texture.h"
#include "Core/Logger/Logger.h"
#include "Core/AssetManager/AssetManager.h"
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
    m_width = 200;
    m_height = 200;
    m_imageSize[0] = 256;
    m_imageSize[1] = 256;

    m_texture = new TextureGenEngine::Texture();
    m_textureData = new TextureData(m_imageSize[0], m_imageSize[1]);
    m_background->ChangeColor(1.0f, 1.0f, 1.0f, 1.0f);
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
        m_background->ChangeTexture(m_texture);
        m_texture->UpdateTexture(m_textureData);
        m_needsUpdate = false;
        if (m_onImageChange)
        {
            m_onImageChange();
        }
    }
}

void TextureGenEngine::ImagePreviewElement::SetImageSize(int width, int height)
{
    LOG_DEBUG("Setting image size %d %d\n", width, height);
    m_imageSize[0] = width;
    m_imageSize[1] = height;
    m_textureData->SetSize(m_imageSize[0], m_imageSize[1]);
    m_texture->UpdateTexture(m_textureData);
}


 void TextureGenEngine::ImagePreviewElement::LoadingScreen()
{
  ImageData imgData = TextureGenEngine::LoadImage("loading.png");
  m_texture->UpdateTexture(imgData.data, imgData.width, imgData.height, imgData.channels);
  //m_background->RemoveTexture();
}

void TextureGenEngine::ImagePreviewElement::UpdateImage()
{
  m_needsUpdate = true;
}

TextureGenEngine::TextureData *TextureGenEngine::ImagePreviewElement::GetImageData()
{
  return m_textureData;
}

 void TextureGenEngine::ImagePreviewElement::SetTextureData(TextureData *data)
{
    if (data != m_textureData)
    {
        delete m_textureData;
        m_textureData = nullptr;
    }
    m_textureData = data;
    m_needsUpdate = true;
}

void TextureGenEngine::ImagePreviewElement::SetOnImageChange(std::function<void()> onImageChange)
{
    m_onImageChange = onImageChange;
}

unsigned char* TextureGenEngine::ImagePreviewElement::GetCharData()
{
    return m_textureData->GetRawData();
}