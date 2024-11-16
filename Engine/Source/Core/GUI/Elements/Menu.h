#include "Defines.h"
#include "BaseElement.h"
#include <string>

namespace TextureGenEngine
{
    class Text;
    class Menu : public BaseElement
    {
    private:
        std::string m_title = "MenuPlaceholder";
        Text* m_text;

    public:
        TAPI Menu(std::string title);
        void UpdatePosition(int x, int y); 
        void UpdatePosition(int x);  
        void Draw() override;
        ~Menu();
    };
} // namespace name
