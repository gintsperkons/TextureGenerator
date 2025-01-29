#include "ImagePreviewElement.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Renderer/TextureData.h"
#include "Core/Renderer/Texture.h"

#include "FastNoise/FastNoise.h"
#include "FastSIMD/FastSIMD.h"
#define FASTNOISE_SIMD_NONE

#include <random>
#include <iostream>

TextureGenEngine::ImagePreviewElement::ImagePreviewElement()
{
    m_texture = new TextureGenEngine::Texture();
    m_textureData = new TextureData(100, 100);
    m_texture->LoadTexture(m_textureData);
    m_background->ChangeTexture(m_texture);
    std::vector<float> data(100 * 100);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 264655);
    auto fn = FastNoise::New<FastNoise::Perlin>(FastSIMD::Level_SSE2);
    if (!fn)
    {
        std::cout << "Failed to create FastNoise node" << std::endl;
        return;
        }
        fn->GenTileable2D(data.data(), 100, 100, 0.1f, dis(gen));



    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 100; j++)
        {
            std::cout << data[i * 100 + j] << " \n";
            int color = (data[i * 100 + j] + 1) * 127.5;
            m_textureData->SetPixel(i, j, Pixel(color, color, color, 0XFF));
        }
    }
    m_texture->UpdateTexture(m_textureData);
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
    m_background->SetPosition(x, y-m_height);

}
