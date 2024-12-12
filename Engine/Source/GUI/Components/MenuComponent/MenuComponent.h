#pragma once
#include "Defines.h"
#include "GUI/Components/Component.h"
namespace TextureGenEngine
{
    class MenuComponent : public Component
    {
    private:
        /* data */
    public:
        MenuComponent(int height = MenuComponent::height);
        void Init(int width, int height) override;
        void Draw() override;
        void Resize(int width, int height) override;
        ~MenuComponent();
        static inline int height = 25;
    };

} // namespace TextureGenEngine
