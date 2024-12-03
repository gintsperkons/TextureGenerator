#pragma once
#include "Defines.h"
#include "GUI/Components/Component.h"
namespace TextureGenEngine
{
    class MenuComponent: public Component
    {
    private:
        /* data */
    public:
        MenuComponent(int height = 50);
        void Draw() override;
        ~MenuComponent();
    };
    
} // namespace TextureGenEngine
 