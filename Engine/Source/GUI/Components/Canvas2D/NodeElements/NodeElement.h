#pragma once
#include "Defines.h"
#include "GUI/Components/Component.h"
#include <string>

namespace TextureGenEngine
{
    class Node;
    class OutputConnector;
    class InputConnector;
    class NodeElement : public Component
    {
    protected:
        std::string m_elementType;
        InputConnector *m_inputImage;
        OutputConnector *m_outputImage;
        Node* m_node;
        std::string m_dataType;

    public:
        NodeElement(/* args */);
        ~NodeElement();
        virtual void OnMouseDrag(double x, double y) override;
        virtual void Setup(int x, int y);
        virtual void SetManager(GUIManager *manager) override;
        virtual void SetNode(Node* node) { m_node = node; }
        virtual Component *SelectObject(double x, double y) override;
        InputConnector *GetInputConnector(double x, double y);
        Node * GetNode() { return m_node; }
    };
} // namespace TextureGenEngine
