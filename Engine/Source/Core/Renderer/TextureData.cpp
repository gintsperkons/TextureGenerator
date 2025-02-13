#include "TextureData.h"


TextureGenEngine::TextureData::TextureData(int width, int height)
    : m_width(width), m_height(height), m_channels(4), m_pixels(width * height)
{
}

TextureGenEngine::TextureData::~TextureData()
{
}

void TextureGenEngine::TextureData::SetPixel(int x, int y, TextureGenEngine::Pixel pixel)
{
    if (x >= 0 && x < m_width && y >= 0 && y < m_height)
    {
        m_pixels[y * m_width + x] = pixel;
    }
}

TextureGenEngine::Pixel TextureGenEngine::TextureData::GetPixel(int x, int y)
{
    if (x >= 0 && x < m_width && y >= 0 && y < m_height)
    {
        return m_pixels[y * m_width + x];
    }
    return 0x00000000;
}

void TextureGenEngine::TextureData::SetSize(int width, int height)
{
    m_width = width;
    m_height = height;
    m_pixels.resize(width * height);
}

void TextureGenEngine::TextureData::UpdatePixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    if (x >= 0 && x < m_width && y >= 0 && y < m_height)
    {
        m_pixels[y * m_width + x] = TextureGenEngine::Pixel(r, g, b, a);
    }
}

unsigned char *TextureGenEngine::TextureData::GetRawData()
{
    unsigned char *data = new unsigned char[m_width * m_height * m_channels];
    for (int i = 0; i < m_width * m_height; i++)
    {
        data[i * m_channels] = m_pixels[i].GetR();
        data[i * m_channels + 1] = m_pixels[i].GetG();
        data[i * m_channels + 2] = m_pixels[i].GetB();
        data[i * m_channels + 3] = m_pixels[i].GetA();
    }
    return data;
}

bool TextureGenEngine::TextureData::Valid()
{
    return m_width > 0 && m_height > 0 && m_pixels.size() >= m_width * m_height;
}
