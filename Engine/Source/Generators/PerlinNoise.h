#pragma once
#include "Defines.h"

namespace TextureGenEngine
{
    namespace PatternGenerator
    {
        namespace Perlin
        {
            TAPI void GenTileable2D(float *data, int width, int height, float frequency, int seed);
        }
    }

} // namespace TextureGenEngine
