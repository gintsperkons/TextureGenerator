#pragma once
#include "Defines.h"
#include "MenuComponent.h"

namespace TextureGenEngine
{
    class MenuBar: public MenuComponent
    {
    private:
        /* data */
    public:
        TAPI MenuBar();
        void Draw() override;
        ~MenuBar();
    };
    
} // namespace TextureGenEngine
