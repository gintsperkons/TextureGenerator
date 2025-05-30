#pragma once
#include "Defines.h"
#include <vector>

namespace TextureGenEngine
{
  struct Pixel
  {
    unsigned int pixel;
    // 0xrrggbbaa
    Pixel(unsigned int pixel)
        : pixel(pixel) {}
    Pixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
      pixel = (r << 24) | (g << 16) | (b << 8) | a;
    }
    Pixel()
    {
      pixel = 0x00FF00FF;
    }
    void Set(unsigned int pixel)
    {
      this->pixel = pixel;
    }
    void Set(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
      pixel = (r << 24) | (g << 16) | (b << 8) | a;
    }
    unsigned char GetR() const { return (pixel >> 24) & 0xFF; }
    unsigned char GetG() const { return (pixel >> 16) & 0xFF; }
    unsigned char GetB() const { return (pixel >> 8) & 0xFF; }
    unsigned char GetA() const { return pixel & 0xFF; }

    void Copy(const Pixel &other)
    {
      this->pixel = other.pixel; // Copy the pixel data
    }
  };
  class TextureData
  {
  private:
    int m_width = 0;
    int m_height = 0;
    int m_channels = 0;
    std::vector<TextureGenEngine::Pixel> m_pixels;

  public:
   TAPI  TextureData(int width, int height);
    ~TextureData();
    void SetPixel(int x, int y, TextureGenEngine::Pixel pixel);
    TAPI void SetPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    TAPI TextureGenEngine::Pixel GetPixel(int x, int y);
    void SetSize(int width, int height);
    void UpdatePixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }
    int GetChannels() const { return m_channels; }
    std::vector<Pixel> GetPixels() const { return m_pixels; }
    unsigned char *GetRawData();
    TAPI void MergeByFloat(TextureData *data1, TextureData *data2, float factor);
    TAPI void MergeByImage(TextureData *data1, TextureData *data2, TextureData *data3);
    TAPI void BinaryThreshold(TextureData *data1, int threshold);
    TAPI void Dialate(TextureData *data1, int size);
    TAPI void Erode(TextureData *data1, int size);
    TAPI void WierdEffect(TextureData *data1, int size);
    TAPI void Mask(TextureData *image, TextureData *mask);
    TAPI void Invert(TextureData *image);
    TAPI void Color(int r, int g, int b, int a);
    TAPI void ColorToTransparent(TextureData*data, int r, int g, int b, float strength);
    TAPI void Overlay(TextureData *image, TextureData *data);
    TAPI void Multiply(TextureData *image, float factor);
    void Delete();
    bool Valid();
  };
} // namespace TextureGenEngine
