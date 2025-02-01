#include "CellularNoise.h"
#include "FastNoise/FastNoise.h"
#include "FastSIMD/FastSIMD.h"

void TextureGenEngine::PatternGenerator::Cellular::GenTileable2D(float *data, int width, int height, float frequency, int seed)
{
    auto fn = FastNoise::New<FastNoise::CellularDistance    >(FastSIMD::Level_SSE2);
    fn->GenTileable2D(data, width, height, frequency, seed);
}