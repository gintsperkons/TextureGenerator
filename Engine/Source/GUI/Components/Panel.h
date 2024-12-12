#pragma once
#include "Defines.h"
#include "Component.h"
#include "GUI/ScalingType.h"

namespace TextureGenEngine
{
    class Panel: public Component
    {
        ScalingType m_scalingTypeX;
        ScalingType m_scalingTypeY;

    public:
        TAPI Panel(int x, int y, int width, int height, ScalingType xScaling, ScalingType yScaling);
        void Init(int width, int height) override;
        void Resize(int width, int height) override;
        Component *SelectObject(double x, double y) override { return nullptr; };
        ~Panel();
    };

} // namespace TextureGenEngine
