#pragma once
#include "Defines.h"
#include "GUI/Components/Panel.h"
#include "GUI/ScalingType.h"
#include <vector>

namespace TextureGenEngine
{
    class Node;
    class InputConnector;
    class OutputConnector;
    class Canvas2D : public Panel
    {
        std::vector<Node *> m_nodes;
    public:
        TAPI Canvas2D(int x, int y, int width, int height, ScalingType xScaling, ScalingType yScaling);
        void Draw() override;
        ~Canvas2D();
        void TAPI AddNode(Node *node);
        Component *SelectObject(double x, double y) override;
        void OnMouseDrag(double x, double y) override;
        InputConnector* GetInputConnector(double x, double y);
        OutputConnector* GetOutputConnector(double x, double y);
    };
} // namespace TextureGenEngine