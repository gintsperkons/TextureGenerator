#pragma once
#include "Defines.h"
#include "NodeElement.h"

namespace TextureGenEngine
{
    class TextureData;
    class Texture;
    class ImagePreviewElement : public NodeElement
    {
    private:
        TextureData* m_textureData = nullptr;
        Texture* m_texture = nullptr;
        int m_seed = 0;
        float m_frequency = 0.1f;

    public:
        TAPI ImagePreviewElement(/* args */);
        ~ImagePreviewElement();
        void OnMouseDrag(float x, float y) override;
        void Setup(float x, float y) override;
        TAPI void GetFrequency(float &frequency);
        TAPI void SetFrequency(float frequency);
        TAPI void GetSeed(int &seed);
        TAPI void SetSeed(int seed);

    };

} // namespace TextureGenEngine
