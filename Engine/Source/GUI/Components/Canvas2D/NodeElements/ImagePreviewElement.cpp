#include "ImagePreviewElement.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Renderer/TextureData.h"
#include "Core/Renderer/Texture.h"
#include "Core/Logger/Logger.h"

#include "FastNoise/FastNoise.h"
#include "FastSIMD/FastSIMD.h"
#define FASTNOISE_SIMD_NONE

#include <random>
#include <iostream>

TextureGenEngine::ImagePreviewElement::ImagePreviewElement()
{
    m_x = 0;
    m_y = 0;
    m_width = 100;
    m_height = 100;

    m_frequency = 0.1f;

    m_texture = new TextureGenEngine::Texture();
    m_textureData = new TextureData(100, 100);
    m_texture->LoadTexture(m_textureData);
    m_background->ChangeTexture(m_texture);
    std::vector<float> data(100 * 100);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 264655);
    m_seed = dis(gen);
    auto fn = FastNoise::New<FastNoise::Perlin>(FastSIMD::Level_SSE2);
    if (!fn)
    {
        std::cout << "Failed to create FastNoise node" << std::endl;
        return;
    }
    fn->GenTileable2D(data.data(), 100, 100, m_frequency, m_seed);

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
    NodeElement::Setup(x + 20, y - m_height + 20);
    m_background->SetPosition(m_x, m_y);
    LOG_DEBUG("Setting up ImagePreviewElement\n");
    LOG_DEBUG("position %f %f\n", m_x, m_y);
}

void TextureGenEngine::ImagePreviewElement::GetFrequency(float &frequency)
{
    frequency = m_frequency;
}

void TextureGenEngine::ImagePreviewElement::SetFrequency(float frequency)
{
    m_frequency = frequency;

    auto fn = FastNoise::New<FastNoise::Perlin>(FastSIMD::Level_SSE2);
    if (!fn)
    {
        std::cout << "Failed to create FastNoise node" << std::endl;
        return;
    }
    std::vector<float> data(100 * 100);

    fn->GenTileable2D(data.data(), 100, 100, m_frequency, m_seed);

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

void TextureGenEngine::ImagePreviewElement::GetSeed(int &seed)
{
    seed = m_seed;
}

void TextureGenEngine::ImagePreviewElement::SetSeed(int seed)
{
    m_seed = seed;

    auto fn = FastNoise::New<FastNoise::Perlin>(FastSIMD::Level_SSE2);
    if (!fn)
    {
        std::cout << "Failed to create FastNoise node" << std::endl;
        return;
    }
    std::vector<float> data(100 * 100);

    fn->GenTileable2D(data.data(), 100, 100, m_frequency, m_seed);

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
