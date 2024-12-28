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
      std::string m_textString;
    public:
        TAPI Label(float x, float y, float width, float height, const std::string &text);
         void SetText(const std::string &text);

        ~Label();
        void Draw() override;
   };
} // namespace TextureGenEngine
