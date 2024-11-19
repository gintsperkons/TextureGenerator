#include "Defines.h"
#include "Core/GUI/SubElements/BaseElement.h"
#include "Core/GUI/Structures.h"
#include <string>

namespace TextureGenEngine
{
    class TextElement;
    class Menu : public BaseElement
    {
    private:
        std::string m_title = "MenuPlaceholder";
        TextElement *m_text;

    public:
        TAPI Menu(std::string title);
        void UpdatePosition(int x, int y);
        void UpdatePosition(int x);
        void Draw() override;
        ~Menu();
    };
} // namespace name
