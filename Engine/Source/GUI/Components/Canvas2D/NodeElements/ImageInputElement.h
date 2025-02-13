#pragma once
#include "Defines.h"
#include "NodeElement.h"
#include "NodeTypes.h"

namespace TextureGenEngine
{
  class TextureData;
  class Texture;
  class ImageInputElement : public NodeElement
  {
  private:
    TextureData *m_textureData = nullptr;

  public:
    TAPI ImageInputElement(/* args */);
    ~ImageInputElement();
    virtual void Draw() override;
    virtual void Init(float width, float height) override;
    virtual void Setup(float x, float y) override;
    virtual void OnMouseDrag(float x, float y) override;
    virtual void UpdateData(TextureData *data);
    TAPI TextureData *GetData();
  };

} // namespace TextureGenEngine
