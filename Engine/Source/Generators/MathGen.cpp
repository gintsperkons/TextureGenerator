#define _USE_MATH_DEFINES // This must be defined before including <cmath>
#include <cmath>
#include <algorithm>
#include "MathGen.h"
#include "Core/Logger/Logger.h"


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

void TextureGenEngine::PatternGenerator::RotatableLine::GenTileable2D(float *data, int width, int height, float frequency, float amplitude,float angle,float offset)
{
  if (!data || width <= 0 || height <= 0)
    return;
  float radAngle = angle * M_PI / 180.f;
  float sinAngle = std::sin(radAngle);
  float cosAngle = std::cos(radAngle);
  float projectedWidth = std::abs(width * cosAngle) + std::abs(height * sinAngle);
  frequency = frequency * M_PI / projectedWidth; // Ensures seamless tiling
  float centerX = width / 2.0f;
  float centerY = height / 2.0f;

  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      // Offset coordinates to center
      float offsetX = x - centerX;
      float offsetY = y - centerY;

      // Project (offsetX, offsetY) onto the perpendicular axis of the angle
      float distance = offsetX * cosAngle + offsetY * sinAngle;
      float value = amplitude * std::sin(distance * frequency*2 + M_PI*1.5f);
      value = std::clamp(value, -1.0f, 1.0f);

      data[y * width + x] = value;
    }
  }
}

void TextureGenEngine::PatternGenerator::CircleGrid::GenTileable2D(float *data, int width, int height, int frequency, float amplitude, float radius)
{
  if (!data || width <= 0 || height <= 0 || frequency <= 0)
    return;

  // Recalculate the radius if it's dependent on width/frequency
  int calcRadius = std::min(width, height) / frequency / 2;

  // Loop over the grid
  for (int cx = 0; cx < frequency; ++cx)
  {
    for (int cy = 0; cy < frequency; ++cy)
    {
      // Calculate the center of each circle in the grid
      float centerX = cx * width / frequency + calcRadius;
      float centerY = cy * height / frequency + calcRadius;

      // Loop over the pixels within each circle
      for (int y = static_cast<int>(centerY - calcRadius-1); y <= static_cast<int>(centerY + calcRadius); ++y)
      {
        for (int x = static_cast<int>(centerX - calcRadius-1); x <= static_cast<int>(centerX + calcRadius); ++x)
        {
          // Ensure x and y are within bounds
          if (x >= 0 && x < width && y >= 0 && y < height)
          {
            // Calculate the distance from the center of the circle
            float distance = std::sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));

            // If within radius, generate sine wave pattern
            
              float value = amplitude * std::sin(distance * M_PI_2 / radius - M_PI_2);
              value = std::clamp(value, -1.0f, 1.0f);
              data[y * width + x] = value;
            
          }
        }
      }
    }
  }
}
