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

    public:
        TAPI ImagePreviewElement(/* args */);
        ~ImagePreviewElement();
        void OnMouseDrag(float x, float y) override;
        void Setup(float x, float y) override;
    };

} // namespace TextureGenEngine
