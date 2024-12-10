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
    ~IntegerElement() ;
   };
} // namespace TextureGenEngine
