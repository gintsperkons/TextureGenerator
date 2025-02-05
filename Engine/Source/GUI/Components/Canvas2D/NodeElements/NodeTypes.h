#pragma once
#include "Defines.h"
#include <functional>

namespace TextureGenEngine
{
    enum class NodeDataTypes
    {
        NONE,
        TEXT,
        INTEGER,
        FLOAT,
        IMAGE,
        PATTERNGENERATOR,
    };

    struct PatternGeneratorData
    {
        float frequency;
        int seed;
        int type;
        std::function < void(float*, int, int, float, int)> generator;
    };

    enum class PatternGenerationTypes
    {
        NOISE,
        MATH,
        MERGE,
        MANIPULATION,

    };
} // namespace TextureGenEngine
