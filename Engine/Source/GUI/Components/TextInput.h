#include "GUI/Components/Component.h"
#include <string>

namespace TextureGenEngine
{
    class TextElement;
    class Text;
    class Mesh;
    class TextInput : public Component
    {

        Text *m_textMesh = nullptr;
        Mesh *m_cursor = nullptr;
        std::string m_text;
        bool m_showCursor = false;
        int m_cursorPosition = 0;
        float m_textDrawOffset = 0;

        void CheckCursorInView();
    public:
        TAPI TextInput(int x, int y, int width, int height);
        ~TextInput();
        void Draw() override;
        void AddChar(unsigned int codepoint);
        void RemoveChar();
        void Select() override { m_showCursor = true; };
        void DeSelect() override { m_showCursor = false; };
        void MoveCursorLeft();
        void MoveCursorRight();
    };
}
