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
        virtual void OnMouseDrag(float x, float y) override;
        virtual void Setup(float x, float y);
        virtual void SetManager(GUIManager *manager) override;
        virtual void SetNode(Node* node) { m_node = node; }
        virtual Component *SelectObject(float x, float y) override;
        InputConnector *GetInputConnector(float x, float y);
        OutputConnector *GetOutputConnector(float x, float y);
        Node * GetNode() { return m_node; }
    };
} // namespace TextureGenEngine
