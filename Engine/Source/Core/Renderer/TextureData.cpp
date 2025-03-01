#include "TextureData.h"
#include "Core/Logger/Logger.h"
#include <algorithm>

TextureGenEngine::TextureData::TextureData(int width, int height)
    : m_width(width), m_height(height), m_channels(4), m_pixels(width * height)
{
}

TextureGenEngine::TextureData::~TextureData()
{
  m_pixels.clear();
  m_width = 0;
  m_height = 0;
  m_channels = 0;
}

void TextureGenEngine::TextureData::SetPixel(int x, int y, TextureGenEngine::Pixel pixel)
{
  if (x >= 0 && x < m_width && y >= 0 && y < m_height)
  {
    m_pixels[y * m_width + x] = pixel;
  }
}

void TextureGenEngine::TextureData::SetPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
  if (x >= 0 && x < m_width && y >= 0 && y < m_height)
  {
    m_pixels[y * m_width + x].Set((r << 24) | (g << 16) | (b << 8) | a);
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

void TextureGenEngine::TextureData::MergeByFloat(TextureData *data1, TextureData *data2, float factor)
{
  LOG_DEBUG("Merging by float\n");
  if (!data1 || !data2)
    return;
  if (!data1->Valid() || !data2->Valid() || data1->GetWidth() != data2->GetWidth() || data1->GetHeight() != data2->GetHeight() || data1->GetChannels() != data2->GetChannels())
  {
    return;
  }
  LOG_DEBUG("Merging by 122222\n");
  LOG_DEBUG("Width: %d\n", data1->GetWidth());
  m_pixels.resize(data1->GetWidth() * data1->GetHeight());
  for (int x = 0; x < data1->GetWidth(); x++)
  {
    for (int y = 0; y < data1->GetHeight(); y++)
    {
      TextureGenEngine::Pixel pixel1 = data1->GetPixel(x, y);
      TextureGenEngine::Pixel pixel2 = data2->GetPixel(x, y);
      int r = (pixel2.GetR()) * factor + (pixel1.GetR()) * (1.0f - factor);
      int g = (pixel2.GetG()) * factor + (pixel1.GetG()) * (1.0f - factor);
      int b = (pixel2.GetB()) * factor + (pixel1.GetB()) * (1.0f - factor);
      int a = (pixel2.GetA()) * factor + (pixel1.GetA()) * (1.0f - factor);
      SetPixel(x, y, r, g, b, a);
    }
  }
  LOG_DEBUG("Merging by 333333\n");
}

void TextureGenEngine::TextureData::BinaryThreshold(TextureData *data1, int threshold)
{
  if (!data1)
    return;
  if (!data1->Valid())
  {
    return;
  }
  m_pixels.resize(data1->GetWidth() * data1->GetHeight());
  for (int x = 0; x < data1->GetWidth(); x++)
  {
    for (int y = 0; y < data1->GetHeight(); y++)
    {
      TextureGenEngine::Pixel pixel1 = data1->GetPixel(x, y);
      if (pixel1.GetR() > threshold)
      {
        SetPixel(x, y, 255, 255, 255, 255);
      }
      else
      {
        SetPixel(x, y, 0, 0, 0, 255);
      }
    }
  }
}

void TextureGenEngine::TextureData::Mask(TextureData *image, TextureData *mask)
{
  if (!image || !mask)
    return;
  if (!image->Valid() || !mask->Valid() || image->GetWidth() != mask->GetWidth() || image->GetHeight() != mask->GetHeight() || image->GetChannels() != mask->GetChannels())
  {
    return;
  }
  m_pixels.resize(image->GetWidth() * image->GetHeight());
  for (int x = 0; x < image->GetWidth(); x++)
  {
    for (int y = 0; y < image->GetHeight(); y++)
    {
      TextureGenEngine::Pixel pixel1 = image->GetPixel(x, y);
      TextureGenEngine::Pixel pixel2 = mask->GetPixel(x, y);

      int r = static_cast<int>(pixel1.GetR() * (1.0f - pixel2.GetR() / 255.0f) + 255.0f * pixel2.GetR() / 255.0f);
      int g = static_cast<int>(pixel1.GetG() * (1.0f - pixel2.GetG() / 255.0f) + 255.0f * pixel2.GetG() / 255.0f);
      int b = static_cast<int>(pixel1.GetB() * (1.0f - pixel2.GetB() / 255.0f) + 255.0f * pixel2.GetB() / 255.0f);
      int a = 255;
      SetPixel(x, y, r, g, b, a);
    }
  }
}

void TextureGenEngine::TextureData::Invert(TextureData *image)
{
  if (!image)
    return;
  if (!image->Valid())
  {
    return;
  }
  m_pixels.resize(image->GetWidth() * image->GetHeight());
  for (int x = 0; x < image->GetWidth(); x++)
  {
    for (int y = 0; y < image->GetHeight(); y++)
    {
      TextureGenEngine::Pixel pixel1 = image->GetPixel(x, y);
      SetPixel(x, y, 255 - pixel1.GetR(), 255 - pixel1.GetG(), 255 - pixel1.GetB(), pixel1.GetA());
    }
  }
}

void TextureGenEngine::TextureData::Color(int r, int g, int b, int a)
{
 r = std::clamp(r, 0, 255);
 g = std::clamp(g, 0, 255);
 b = std::clamp(b, 0, 255);
 a = std::clamp(a, 0, 255);
  for (int x = 0; x < m_width; x++)
  {
    for (int y = 0; y < m_height; y++)
    {
      SetPixel(x, y, r, g, b, a);
    }
  }
}

void TextureGenEngine::TextureData::Delete()
{
	m_pixels.clear();
	m_width = 0;
	m_height = 0;
	m_channels = 0;
}

bool TextureGenEngine::TextureData::Valid()
{
  return m_width > 0 && m_height > 0 && m_pixels.size() >= m_width * m_height;
}
