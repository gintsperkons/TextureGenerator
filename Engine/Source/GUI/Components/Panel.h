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
        TAPI Panel(float x, float y, float width, float height, ScalingType xScaling, ScalingType yScaling);
        void Init(float width, float height) override;
        void Resize(float width, float height) override;
        Component *SelectObject(float x, float y) override { return nullptr; };
        ~Panel();
    };

} // namespace TextureGenEngine
