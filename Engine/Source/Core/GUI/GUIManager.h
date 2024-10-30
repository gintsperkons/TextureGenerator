#pragma once
#include "Defines.h"

namespace TextureGenEngine
{
    class GUIManager
    {
    private:
        /* data */
    public:
        TAPI GUIManager(int width, int height);
        void Draw();
        ~GUIManager();
    };
} // namespace TextureGenEngine
