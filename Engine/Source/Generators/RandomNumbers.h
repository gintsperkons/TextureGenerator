#pragma once
#include "Defines.h"
#include <string>

namespace TextureGenEngine
{
    namespace Random
    {
        TAPI int RandInt(int min, int max);
        TAPI std::string UUID();

    } // namespace Random

} // namespace TextureGenEngine
