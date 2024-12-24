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
        MenuComponent(float height = MenuComponent::height);
        void Init(float width, float height) override;
        void Draw() override;
        void Resize(float width, float height) override;
        ~MenuComponent();
        static inline float height = 25;
    };

} // namespace TextureGenEngine
