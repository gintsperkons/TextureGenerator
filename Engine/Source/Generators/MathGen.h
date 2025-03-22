#pragma once
#include "Defines.h"

namespace TextureGenEngine
{
  namespace PatternGenerator
  {
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
