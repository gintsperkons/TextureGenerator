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
        void OnHover(float x, float y) override;
        void Resize(float width, float height) override;
        void SetMenuBar(float x, float y, float width, float height);
        ~Menu();
    };

} // namespace TextureGenEngine