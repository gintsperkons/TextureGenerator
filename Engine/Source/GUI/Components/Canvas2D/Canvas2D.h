#pragma once
#include "Defines.h"
#include "GUI/Components/Panel.h"
#include "GUI/ScalingType.h"

namespace TextureGenEngine
{
    class Canvas2D : public Panel
    {
        
    public:
        TAPI Canvas2D(int x, int y, int width, int height, ScalingType xScaling, ScalingType yScaling);
        void Draw() override;
        ~Canvas2D();
    };
} // namespace TextureGenEngine