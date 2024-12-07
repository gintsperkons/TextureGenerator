#pragma once
#include "Defines.h"
#include "GUI/Components/Component.h"

namespace TextureGenEngine
{
    class Node : public Component
    {
    public:
        TAPI Node(int x, int y, int width, int height);
        void Init(int width, int height) override;
        bool CheckCollision(float x, float y) override;
        ~Node();
    };
}
