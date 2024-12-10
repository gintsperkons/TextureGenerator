#pragma once
#include "Defines.h"
#include "GUI/Components/Component.h"

namespace TextureGenEngine
{
    class Mesh;
    class Node : public Component
    {
        Mesh *m_dataBackground = nullptr;

    public:
        TAPI Node(int x, int y);
        void Init(int width, int height) override;
        void Draw() override;
        void OnMouseDrag(double x, double y) override;
        bool CheckCollision(float x, float y) override;
        ~Node();

        static inline int c_titleHeight = 25;
    };
}
