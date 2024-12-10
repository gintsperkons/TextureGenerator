#pragma once
#include "Defines.h"
#include "GUI/Components/Component.h"
#include <vector>

namespace TextureGenEngine
{
    class NodeElement;
    class Mesh;
    class Node : public Component
    {
        Mesh *m_dataBackground = nullptr;
    std::vector<NodeElement *> m_elements;
    public:
        TAPI Node(int x, int y);
        void Init(int width, int height) override;
        void Draw() override;
        void TAPI AddElement(NodeElement *element);
        void OnMouseDrag(double x, double y) override;
        bool CheckCollision(float x, float y) override;
        ~Node();

        static inline int c_titleHeight = 25;
    };
}
