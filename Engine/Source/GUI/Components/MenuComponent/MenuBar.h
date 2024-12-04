#pragma once
#include "Defines.h"
#include "MenuComponent.h"
#include <vector>

namespace TextureGenEngine
{
    class MenuBar: public MenuComponent
    {
    private:
        std::vector<MenuComponent*> m_menus;
    public:
        TAPI MenuBar();
        void Init(int width, int height) override;
        void Draw() override;
        void Resize(int width, int height) override;
        TAPI void AddMenu(MenuComponent* menu);
        ~MenuBar();
    };
    
} // namespace TextureGenEngine
