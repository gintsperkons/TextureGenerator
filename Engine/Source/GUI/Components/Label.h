#pragma once
#include "Defines.h"
#include "Component.h"
#include <string>

namespace TextureGenEngine
{
   class Label: public Component
   {
    public:
        TAPI Label(int x, int y, int width, int height, const std::string &text);
        ~Label();
        void Draw() override;
   };
} // namespace TextureGenEngine
