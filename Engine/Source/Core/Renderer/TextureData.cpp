#include "TextureData.h"
#include "Core/Logger/Logger.h"
#include <algorithm>
#include <cmath>

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

void TextureGenEngine::TextureData::MergeByImage(TextureData *data1, TextureData *data2, TextureData *data3)
{

  if (!data1 || !data2 || !data3)
    return;

  if (!data1->Valid() || !data2->Valid() || !data3->Valid() ||
      data1->GetWidth() != data2->GetWidth() || data1->GetWidth() != data3->GetWidth() ||
      data1->GetHeight() != data2->GetHeight() || data1->GetHeight() != data3->GetHeight() ||
      data1->GetChannels() != data2->GetChannels() || data1->GetChannels() != data3->GetChannels())
  {
    return;
  }


  m_pixels.resize(data1->GetWidth() * data1->GetHeight());

  for (int x = 0; x < data1->GetWidth(); x++)
  {
    for (int y = 0; y < data1->GetHeight(); y++)
    {
      TextureGenEngine::Pixel pixel1 = data1->GetPixel(x, y);
      TextureGenEngine::Pixel pixel2 = data2->GetPixel(x, y);
      TextureGenEngine::Pixel pixel3 = data3->GetPixel(x, y);

      float factor = ((int)pixel3.GetR() / 255.0f + (int)pixel3.GetG() / 255.0f + (int)pixel3.GetB() / 255.0f) / 3;

      int r = (pixel2.GetR()) * factor + (pixel1.GetR()) * (1.0f - factor);
      int g = (pixel2.GetG()) * factor + (pixel1.GetG()) * (1.0f - factor);
      int b = (pixel2.GetB()) * factor + (pixel1.GetB()) * (1.0f - factor);
      int a = (pixel2.GetA()) * factor + (pixel1.GetA()) * (1.0f - factor);
      SetPixel(x, y, r, g, b, a);
    }
  }
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

void TextureGenEngine::TextureData::Dialate(TextureData *data1, int size)
{
  if (!data1 || !data1->Valid())
    return;

  int width = data1->GetWidth();
  int height = data1->GetHeight();
  int channels = data1->GetChannels();

  // Kernel size (Assume a square kernel with odd size, e.g., 3x3, 5x5, etc.)
  int halfSize = size / 2;

  // Intensity threshold for dilation (this can be adjusted based on how sensitive the dilation should be)
  const unsigned char threshold = 32; // This assumes a range from 0 to 255 (grayscale)

  // Iterate over all pixels of the image to apply dilation
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      bool dilated = false; // Flag to indicate whether the current pixel should be dilated

      // Apply the kernel over the neighborhood of each pixel
      for (int ky = -halfSize; ky <= halfSize; ++ky)
      {
        for (int kx = -halfSize; kx <= halfSize; ++kx)
        {
          int nx = x + kx;
          int ny = y + ky;

          // Check if the neighbor is within bounds
          if (nx >= 0 && nx < width && ny >= 0 && ny < height)
          {
            // Calculate the intensity of the neighbor
            Pixel neighborPixel = data1->GetPixel(nx, ny);
            unsigned char intensity = (neighborPixel.GetR() + neighborPixel.GetG() + neighborPixel.GetB()) / 3;

            // If any neighbor has an intensity above the threshold, dilate the current pixel
            if (intensity > threshold)
            {
              dilated = true;
              break; // No need to check further neighbors, the current pixel will be dilated
            }
          }
        }

        if (dilated)
          break;
      }

      // Set the pixel to white if dilated, or keep it black if not
      if (dilated)
      {
        SetPixel(x, y, 255, 255, 255, 255); // Set to white if dilated
      }
      else
      {
        SetPixel(x, y, 0, 0, 0, 255); // Set to black if not dilated
      }
    }
  }
}

void TextureGenEngine::TextureData::Erode(TextureData *data1, int size)
{
  if (!data1 || !data1->Valid())
    return;

  int width = data1->GetWidth();
  int height = data1->GetHeight();
  int channels = data1->GetChannels();

  // Kernel size (Assume a square kernel with odd size, e.g., 3x3, 5x5, etc.)
  int halfSize = size / 2;

  // Intensity threshold for erosion (this can be adjusted based on how sensitive the erosion should be)
  const unsigned char threshold = 32; // This assumes a range from 0 to 255 (grayscale)

  // Iterate over all pixels of the image to apply erosion
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      bool eroded = true; // Flag to indicate whether to erode the current pixel

      // Apply the kernel over the neighborhood of each pixel
      for (int ky = -halfSize; ky <= halfSize; ++ky)
      {
        for (int kx = -halfSize; kx <= halfSize; ++kx)
        {
          int nx = x + kx;
          int ny = y + ky;

          // Check if the neighbor is within bounds
          if (nx >= 0 && nx < width && ny >= 0 && ny < height)
          {
            // Calculate the intensity of the neighbor
            Pixel neighborPixel = data1->GetPixel(nx, ny);
            unsigned char intensity = (neighborPixel.GetR() + neighborPixel.GetG() + neighborPixel.GetB()) / 3;

            // If any neighbor has an intensity below the threshold, erode the current pixel
            if (intensity < threshold)
            {
              eroded = false; // Set flag to erode pixel if any neighbor is below the threshold
              break;
            }
          }
        }

        if (!eroded)
          break;
      }

      // If eroded, set the pixel to black, otherwise keep it white
      if (eroded)
      {
        SetPixel(x, y, 0, 0, 0, 255); // Set to black if eroded
      }
      else
      {
        SetPixel(x, y, 255, 255, 255, 255); // Set to white if not eroded
      }
    }
  }
}

void TextureGenEngine::TextureData::WierdEffect(TextureData *data1, int size)
{
  if (!data1 || !data1->Valid())
    return;

  int width = data1->GetWidth();
  int height = data1->GetHeight();
  int channels = data1->GetChannels();

  // Kernel size (Assume a square kernel with odd size, e.g., 3x3, 5x5, etc.)
  int halfSize = size / 2;

  // Intensity threshold for erosion (this can be adjusted based on how sensitive the erosion should be)
  const unsigned char threshold = 128; // This assumes a range from 0 to 255 (grayscale)

  // Iterate over all pixels of the image to apply erosion
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      int r = data1->GetPixel(x, y).GetR();
      int g = data1->GetPixel(x, y).GetG();
      int b = data1->GetPixel(x, y).GetB();

      int totalIntensity = 0;
      int count = 0;

      // Apply the kernel over the neighborhood of each pixel
      for (int ky = -halfSize; ky <= halfSize; ++ky)
      {
        for (int kx = -halfSize; kx <= halfSize; ++kx)
        {
          int nx = x + kx;
          int ny = y + ky;

          // Check if the neighbor is within bounds
          if (nx >= 0 && nx < width && ny >= 0 && ny < height)
          {
            // Calculate the intensity of the neighbor
            Pixel neighborPixel = data1->GetPixel(nx, ny);
            unsigned char intensity = (neighborPixel.GetR() + neighborPixel.GetG() + neighborPixel.GetB()) / 3;

            totalIntensity += intensity;
            count++;
          }
        }
      }

      SetPixel(x, y, totalIntensity, totalIntensity, totalIntensity, 255);
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

void TextureGenEngine::TextureData::ColorToTransparent(TextureData *data, int r, int g, int b)
{
  // Clamp target color
  r = std::clamp(r, 0, 255);
  g = std::clamp(g, 0, 255);
  b = std::clamp(b, 0, 255);

  // Max possible distance in RGB space
  const float maxDistance = std::sqrt(255 * 255 * 3);

  for (int x = 0; x < data->m_width; ++x)
  {
    for (int y = 0; y < data->m_height; ++y)
    {
      TextureGenEngine::Pixel pixel = data->GetPixel(x, y);

      int pr = pixel.GetR();
      int pg = pixel.GetG();
      int pb = pixel.GetB();

      int dr = pr - r;
      int dg = pg - g;
      int db = pb - b;

      float distance = std::sqrt(float(dr * dr + dg * dg + db * db));
      float transparencyFactor = std::clamp(1.0f - (distance / maxDistance), 0.0f, 1.0f);

      // transparencyFactor is 1.0 when it's the same color => make it fully transparent
      int newAlpha = static_cast<int>(pixel.GetA() * (1.0f - transparencyFactor));

      SetPixel(x, y, pr, pg, pb, newAlpha);
    }
  }
}

void TextureGenEngine::TextureData::Overlay(TextureData *image, TextureData *data)
{
  if (!image || !data)
    return;

  if (!image->Valid() || !data->Valid() ||
      image->GetWidth() != data->GetWidth() ||
      image->GetHeight() != data->GetHeight() ||
      image->GetChannels() != data->GetChannels())
  {
    return;
  }

  int width = image->GetWidth();
  int height = image->GetHeight();

  // Copy base image into this texture
  SetSize(width, height);
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      TextureGenEngine::Pixel base = image->GetPixel(x, y);
      SetPixel(x, y, base.GetR(), base.GetG(), base.GetB(), base.GetA());
    }
  }

  // Apply overlay on top
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      TextureGenEngine::Pixel basePixel = GetPixel(x, y); // already copied
      TextureGenEngine::Pixel overlayPixel = data->GetPixel(x, y);

      float srcAlpha = overlayPixel.GetA() / 255.0f;
      float invAlpha = 1.0f - srcAlpha;

      int outR = static_cast<int>(overlayPixel.GetR() * srcAlpha + basePixel.GetR() * invAlpha);
      int outG = static_cast<int>(overlayPixel.GetG() * srcAlpha + basePixel.GetG() * invAlpha);
      int outB = static_cast<int>(overlayPixel.GetB() * srcAlpha + basePixel.GetB() * invAlpha);
      int outA = static_cast<int>(overlayPixel.GetA() + basePixel.GetA() * invAlpha);

      SetPixel(x, y, outR, outG, outB, outA);
    }
  }
}

void TextureGenEngine::TextureData::Multiply(TextureData *image, float factor)
{
  if (!image || !image->Valid())
    return;

  int width = image->GetWidth();
  int height = image->GetHeight();

  SetSize(width, height); // Assumes this resizes and prepares m_pixels correctly

  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      TextureGenEngine::Pixel pixel = image->GetPixel(x, y);
      int r = static_cast<int>(std::clamp(pixel.GetR() * factor, 0.0f, 255.0f));
      int g = static_cast<int>(std::clamp(pixel.GetG() * factor, 0.0f, 255.0f));
      int b = static_cast<int>(std::clamp(pixel.GetB() * factor, 0.0f, 255.0f));
      SetPixel(x, y, r, g, b, pixel.GetA());
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
