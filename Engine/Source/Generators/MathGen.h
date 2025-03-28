#pragma once
#include "Defines.h"

namespace TextureGenEngine
{
  namespace PatternGenerator
  { namespace RotatableLine 
    {
      TAPI void GenTileable2D(float *data, int width, int height, float frequency, float amplitude, float angle, float offset);
    }
    namespace CircleGrid
    {
      TAPI void GenTileable2D(float *data, int width, int height, int frequency, float amplitude, float radius);
    }
    namespace HorizontalLine
    {
      TAPI void GenTileable2D(float* data, int width, int height,float frequency, float amplitude);
    }
    namespace VerticalLine
    {
      TAPI void GenTileable2D(float *data, int width, int height, float frequency, float amplitude);
    }
    namespace CheckerBoard
    {
      TAPI void GenTileable2D(float *data, int width, int height, float frequency, float amplitude);
    }
  }

} // namespace TextureGenEngine
