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
        void Init(int width,int height) override;
        void Draw() override;
        void Resize(int width, int height) override;
        ~MenuComponent();
    };
    
} // namespace TextureGenEngine
 