#pragma once
#include "Defines.h"
#include "GUI/Components/Component.h"
#include "NodeTypes.h"
#include <string>
#include <functional>

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
        Node *m_node;
        NodeDataTypes m_dataType;
        std::function<void()> m_onDataChange = nullptr;

    public:
        NodeElement(/* args */);
        ~NodeElement();
        virtual void OnMouseDrag(float x, float y) override;
        virtual void Setup(float x, float y);
        virtual void SetManager(GUIManager *manager) override;
        virtual void SetNode(Node *node) { m_node = node; }
        virtual void LockInput() {};
        virtual void UnlockInput() {};
        virtual Component *SelectObject(float x, float y) override;
        InputConnector *GetInputConnector(float x, float y);
        OutputConnector *GetOutputConnector(float x, float y);
        Node *GetNode() { return m_node; }
        std::string GetConnectedOutputs();
        void ConnectInput(Node *outputNode);
        TAPI void
        SetOnDataChange(std::function<void()> onDataChange);
        TAPI void TriggerDataChange();
        virtual void UpdateData(std::string data) {};
        virtual void UpdateData(int data) {};
        virtual void UpdateData(float data) {};
        virtual std::string ExportElementData() { return "-=-"; };
        virtual void ImportElementData(std::string data) {};
    };
} // namespace TextureGenEngine
