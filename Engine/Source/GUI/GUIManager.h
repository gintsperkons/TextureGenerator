#pragma once
#include "Defines.h"

namespace TextureGenEngine
{
    class GUIManager
    {
    public:
        TAPI GUIManager();
        ~GUIManager();
        void Update();
        void Draw();
    };
} // namespace TextureGenEngine
