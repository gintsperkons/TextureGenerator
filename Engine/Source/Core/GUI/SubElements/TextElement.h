#include "Defines.h"
#include <glm/glm.hpp>
#include "Core/GUI/Structures.h"
#include <string>

namespace TextureGenEngine
{
    class Text;
    class TextElement
    {
    private:
        Text * m_text;
        int textSize = 12;

    public:
        TextElement();
        void Draw(std::string text, float x, float y, int frameHeight, int frameWidth, glm::vec3 color, AlignmentHorizontal hAlign, AlignmentVertical vAlign);
        ~TextElement();
    };

} // namespace TextureGenEngine