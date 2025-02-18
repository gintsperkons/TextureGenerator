#pragma once
#include "Defines.h"
#include "MenuComponent.h"
#include <string>
#include <vector>

namespace TextureGenEngine
{
    class Text;
    class MenuBar;
    class MenuItem;
    class Menu : public MenuComponent
    {
    private:
        std::string m_title;
        MenuBar* m_menuBar;
        bool m_opened = false;
        std::vector<MenuItem*> m_menuItems;
        Text* m_text;
    public:
        TAPI Menu(std::string title);
        void Draw() override;
        void Init(float width, float height) override;
        TAPI void AddItem(MenuItem* item);
        void Click(float x, float y) override;
        void OnHover(float x, float y) override;
        void Resize(float width, float height) override;
        void SetMenuBar(float x, float y, float width, float height);
        float GetElementOffset(MenuItem* item);
        ~Menu();
    };

} // namespace TextureGenEngine