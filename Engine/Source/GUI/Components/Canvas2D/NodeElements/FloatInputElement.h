#pragma once
#include "Defines.h"
#include "TextualInputElement.h"

namespace TextureGenEngine
{
    class FloatInputElement: public TextualInputElement
    {
    private:
        /* data */
    public:
        TAPI FloatInputElement(/* args */);
        TAPI void SetData(float data);
        TAPI void GetData(float &data);
        ~FloatInputElement();
    };
    

    
} // namespace TextureGenEngine

