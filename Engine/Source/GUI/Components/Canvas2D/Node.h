#pragma once
#include "Defines.h"
#include "GUI/Components/Component.h"
#include <vector>

namespace TextureGenEngine
{
    class InputConnector;
    class OutputConnector;
    class NodeElement;
    class Mesh;
    class Canvas2D;
    class Node : public Component
    {
        Mesh *m_dataBackground = nullptr;
    std::vector<NodeElement *> m_elements;
    float m_dataBackgroundHeight = 100;
    public:
        TAPI Node(float x, float y);
        void Init(float width, float height) override;
        void Draw() override;
        void TAPI AddElement(NodeElement *element);
        void OnMouseDrag(float x, float y) override;
        bool CheckCollision(float x, float y) override;
        float GetOffset(NodeElement* element);
        Component *SelectObject(float x, float y) override;
        ~Node() override;
        InputConnector* GetInputConnector(float x, float y);
        OutputConnector* GetOutputConnector(float x, float y);
        Canvas2D* GetCanvas();
        static inline float c_titleHeight = 25;
    };
}
