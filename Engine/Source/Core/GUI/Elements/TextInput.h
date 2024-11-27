#include "Core/GUI/SubElements/BaseElement.h"

namespace TextureGenEngine
{
    class TextElement;
    class TextInput : public BaseElement
    {
        TextElement *m_text;

    public:
        TAPI TextInput(int x, int y, int width, int height);
        ~TextInput();
        void Draw() override;
    };
}