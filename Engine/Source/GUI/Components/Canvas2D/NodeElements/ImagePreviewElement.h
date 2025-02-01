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
        std::vector<float> m_imageData;
        Texture* m_texture = nullptr;
        int m_imageSize[2];
    public:
        TAPI ImagePreviewElement(/* args */);
        ~ImagePreviewElement();
        void OnMouseDrag(float x, float y) override;
        void Setup(float x, float y) override;
        TAPI void SetImageSize(int width, int height);
        TAPI int GetImageWidth() { return m_imageSize[0]; };
        TAPI int GetImageHeight() { return m_imageSize[1]; };
        TAPI float* GetImageDataPtr() { return m_imageData.data(); };
        TAPI void UpdateImage();

    };

} // namespace TextureGenEngine
