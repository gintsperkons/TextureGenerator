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
        void Init(float width, float height) override;
        void Draw() override;
        void Resize(float width, float height) override;
        void OnHover(float x, float y) override;
        void Click(float x, float y) override;
        TAPI void AddMenu(MenuComponent* menu);
        ~MenuBar();
    };
    
} // namespace TextureGenEngine
