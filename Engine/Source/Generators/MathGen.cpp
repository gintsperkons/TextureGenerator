#include <cmath>
#include <algorithm>
#include "MathGen.h"

void TextureGenEngine::PatternGenerator::HorizontalLine::GenTileable2D(float *data, int width, int height,float frequency, float amplitude)
{
  if (!data || width <= 0 || height <= 0)
    return;

  frequency = frequency * M_PI / height;  // Ensures seamless tiling

  for (int y = 0; y < height; ++y)
  {
    float value = amplitude * sin(y * frequency); // Normalize to [-1,1]
    value = std::clamp(value,-1.f,1.f);
    for (int x = 0; x < width; ++x)
    { 
      data[y * width + x] = value;
    }
  }
}

void TextureGenEngine::PatternGenerator::VerticalLine::GenTileable2D(float *data, int width, int height, float frequency, float amplitude)
{
  if (!data || width <= 0 || height <= 0)
    return;

  frequency = frequency * M_PI / width; // Ensures seamless tiling

  for (int x = 0; x < width; ++x)
  {
    float value = amplitude * sin(x * frequency); // Generate vertical pattern
    value = std::clamp(value, -1.0f, 1.0f);

    for (int y = 0; y < height; ++y)
    {
      data[y * width + x] = value;
    }
  }
}

void TextureGenEngine::PatternGenerator::CheckerBoard::GenTileable2D(float *data, int width, int height, float frequency, float amplitude)
{
  if (!data || width <= 0 || height <= 0)
    return;

  frequency = frequency * M_PI; // Normalize for tiling

  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      // Checker pattern using sine waves
      float value = amplitude * sin(x * frequency / width) * sin(y * frequency / height);

      // Convert to binary (-1 or 1)
      value = std::clamp(value,-1.0f,1.0f);

      data[y * width + x] = value;
    }
  }
}
