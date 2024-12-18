#pragma once
#include "Defines.h"
#include "GUI/Components/Component.h"
#include <vector>

namespace TextureGenEngine
{
    class InputConnector;
    class NodeElement;
    class Mesh;
    class Canvas2D;
    class Node : public Component
    {
        Mesh *m_dataBackground = nullptr;
    std::vector<NodeElement *> m_elements;
    float m_dataBackgroundHeight = 100;
    public:
        TAPI Node(int x, int y);
        void Init(int width, int height) override;
        void Draw() override;
        void TAPI AddElement(NodeElement *element);
        void OnMouseDrag(double x, double y) override;
        bool CheckCollision(float x, float y) override;
        float GetOffset(NodeElement* element);
        Component *SelectObject(double x, double y) override;
        ~Node();
        InputConnector* GetInputConnector(double x, double y);
        Canvas2D* GetCanvas();
        static inline int c_titleHeight = 25;
    };
}
