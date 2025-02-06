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
        bool m_needsUpdate = false;
        TextureData *m_textureData = nullptr;
        std::vector<float> m_imageData;
        Texture *m_texture = nullptr;
        int m_imageSize[2];

    public:
        TAPI ImagePreviewElement(/* args */);
        ~ImagePreviewElement();
        void OnMouseDrag(float x, float y) override;
        void Setup(float x, float y) override;
        void Draw() override;
        TAPI void SetImageSize(int width, int height);
        TAPI int GetImageWidth() { return m_imageSize[0]; };
        TAPI int GetImageHeight() { return m_imageSize[1]; };
        TAPI float *GetImageDataPtr() { return m_imageData.data(); };
        void UpdateImageBuffer();
        TAPI void UpdateImage();
        TAPI unsigned char *GetCharData();
    };

} // namespace TextureGenEngine
