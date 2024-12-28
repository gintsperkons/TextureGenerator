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
        TAPI Canvas2D(float x, float y, float width, float height, ScalingType xScaling, ScalingType yScaling);
        void Draw() override;
        ~Canvas2D();
        void TAPI AddNode(Node *node);
        Component *SelectObject(float x, float y) override;
        void OnMouseDrag(float x, float y) override;
        InputConnector* GetInputConnector(float x, float y);
        OutputConnector* GetOutputConnector(float x, float y);
        void RemoveChild(Component *child) override;
        TAPI void GetSpawnLocation(float &x, float &y);
    };
} // namespace TextureGenEngine