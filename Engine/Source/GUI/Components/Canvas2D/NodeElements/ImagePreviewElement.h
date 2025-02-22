#pragma once
#include "Defines.h"
#include "NodeElement.h"
#include <functional>

namespace TextureGenEngine
{
  class TextureData;
  class Texture;
  class ImagePreviewElement : public NodeElement
  {
  private:
    bool m_needsUpdate = false;
    TextureData *m_textureData = nullptr;
    Texture *m_texture = nullptr;
    int m_imageSize[2];
    std::function<void()> m_onImageChange = nullptr;

  public:
    TAPI ImagePreviewElement(/* args */);
    ~ImagePreviewElement();
    void OnMouseDrag(float x, float y) override;
    void Setup(float x, float y) override;
    void Draw() override;
    TAPI void SetImageSize(int width, int height);
    TAPI int GetImageWidth() { return m_imageSize[0]; };
    TAPI int GetImageHeight() { return m_imageSize[1]; };
    TAPI void LoadingScreen();
    TAPI void UpdateImage();
    TAPI TextureData *GetImageData();
    TAPI void SetTextureData(TextureData *data);
    TAPI void SetOnImageChange(std::function<void()> onImageChange);
        TAPI unsigned char *
        GetCharData();
  };

} // namespace TextureGenEngine
