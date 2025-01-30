#pragma once
#include "Defines.h"
#include "TextualInputElement.h"

namespace TextureGenEngine
{
   class IntegerElement : public TextualInputElement
   {
   private:
    /* data */
   public:
    TAPI IntegerElement(/* args */) ;
    TAPI void SetData(int data);
    TAPI void GetData(int &data);
    ~IntegerElement() ;
   };
} // namespace TextureGenEngine
