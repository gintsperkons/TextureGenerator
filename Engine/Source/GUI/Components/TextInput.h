#include "GUI/Components/Component.h"
#include <string>

namespace TextureGenEngine
{
    class TextElement;
    class Text;
    class TextInput : public Component
    {

        Text *m_textMesh = nullptr;
        std::string m_text;

    public:
        TAPI TextInput(int x, int y, int width, int height);
        ~TextInput();
        void Draw() override;
        void AddChar(unsigned int codepoint);
        void RemoveChar();
    };
}
