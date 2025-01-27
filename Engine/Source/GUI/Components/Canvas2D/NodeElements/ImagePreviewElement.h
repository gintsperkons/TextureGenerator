#pragma once
#include "Defines.h"
#include "NodeElement.h"

namespace TextureGenEngine
{
    class ImagePreviewElement : public NodeElement
    {
    private:
        /* data */
    public:
        TAPI ImagePreviewElement(/* args */);
        ~ImagePreviewElement();
        void OnMouseDrag(float x, float y) override;
    };

} // namespace TextureGenEngine
