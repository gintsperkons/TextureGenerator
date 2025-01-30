#include "GUI/Components/Component.h"
#include <functional>
#include <string>

namespace TextureGenEngine
{
    enum TextInputType
    {
        TEXT,
        FLOAT,
        INTEGER
    };

    class TextElement;
    class Text;
    class Mesh;
    class TextInput : public Component
    {
    private:
        bool doFilter = false;
        std::string allowedCharacters = "";
        TextInputType m_inputType = TextInputType::TEXT;
        float m_floatValue = 0;
        int m_integerValue = 0;

    protected:
        std::function<void(std::string)> m_onTextChange;
        std::function<void(float)> m_onFloatChange;
        std::function<void(int)> m_onIntegerChange;
        Text *m_textMesh = nullptr;
        Mesh *m_cursor = nullptr;
        std::string m_text = "";
        bool m_enabled = true;
        bool m_showCursor = false;
        int m_cursorPosition = 0;
        float m_textDrawOffset = 0;

        void CheckCursorInView();

    public:
        TAPI TextInput(float x, float y, float width, float height);
        ~TextInput();
        virtual void Init(float width, float height) override;
        void Draw() override;
        void AddChar(unsigned int codepoint);
        void RemoveCharBefore();
        void RemoveCharAfter();
        void Select() override;
        void DeSelect() override { m_showCursor = false; };
        void MoveCursorLeft();
        void MoveCursorRight();
        void SetOnTextChange(std::function<void(std::string)> onTextChange) { m_onTextChange = onTextChange; }
        void SetOnFloatChange(std::function<void(float)> onFloatChange) { m_onFloatChange = onFloatChange; }
        void SetOnIntegerChange(std::function<void(int)> onIntegerChange) { m_onIntegerChange = onIntegerChange; }
        void SetPosition(float x, float y) override;
        void Move(float x, float y) override;
        void Disable();
        void Enable();
        void GetText(std::string &text);
        void SetText(std::string text);
        void GetFloat(float &data);
        void SetFloat(float data);
        void GetInteger(int &data);
        void SetInteger(int data);
        void UpdateData();

        void SetAllowCharacters(std::string characters);
        void SetFilterState(bool filter) { doFilter = filter; }
        void SetInputType(TextInputType type){ m_inputType = type; };
    };
}
