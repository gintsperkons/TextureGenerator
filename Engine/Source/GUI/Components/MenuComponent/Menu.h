#pragma once
#include "Defines.h"
#include "MenuComponent.h"
#include <string>

namespace TextureGenEngine
{
    class Text;
    class MenuBar;
    class Menu : public MenuComponent
    {
    private:
        std::string m_title;
        MenuBar* m_menuBar;
        Text* m_text;
    public:
        TAPI Menu(std::string title);
        void Draw() override;
        void Resize(int width, int height) override;
        void SetMenuBar(int x, int y, int width, int height);
        ~Menu();
    };

} // namespace TextureGenEngine