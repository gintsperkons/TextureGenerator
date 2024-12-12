#pragma once
#include "Defines.h"
#include "Component.h"
#include <string>

namespace TextureGenEngine
{
   class Text;
   class Label: public Component
   {
      Text* m_text = nullptr;
    public:
        TAPI Label(int x, int y, int width, int height, const std::string &text);
        ~Label();
        void Draw() override;
   };
} // namespace TextureGenEngine
