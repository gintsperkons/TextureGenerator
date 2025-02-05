#pragma once
#include "Defines.h"
#include "GUI/Components/Component.h"
#include <vector>
#include <string>

namespace TextureGenEngine
{

    struct NodeInfo
    {
        std::string uuid;
        unsigned int nodeId;
        int position[2] = {0, 0};
        std::vector<std::string> inputConnections;
        std::string elementData = "";
    };

    class InputConnector;
    class OutputConnector;
    class NodeElement;
    class Mesh;
    class Canvas2D;
    class Label;
    class Node : public Component
    {
        OutputConnector *m_outputImage = nullptr;
        Label *m_title = nullptr;
        std::string m_uuid = "";
        unsigned int m_id = 0;
        Mesh *m_dataBackground = nullptr;
        std::vector<NodeElement *> m_elements;
        float m_dataBackgroundHeight = 100;

    public:
        TAPI Node(float x, float y, unsigned int nodeID);
        void Init(float width, float height) override;
        void Draw() override;
        void TAPI AddElement(NodeElement *element);
        void TAPI SetOutput(OutputConnector *output);
        void OnMouseDrag(float x, float y) override;
        bool CheckCollision(float x, float y) override;
        float GetOffset(NodeElement *element);
        Component *SelectObject(float x, float y) override;
        ~Node() override;
        InputConnector *GetInputConnector(float x, float y);
        OutputConnector *GetOutputConnector(float x, float y);
        OutputConnector *GetOutputConnector() { return m_outputImage; }

        TAPI void ConnectInput(Node *outputNode, int inputIndex);
        TAPI void AddElementData(std::string data, int index);

        TAPI NodeInfo GetNodeInfo();
        std::string GetUUID() { return m_uuid; }
        int GetTypeID() { return m_id; }
        std::vector<NodeElement *> GetElements() { return m_elements; }

        Canvas2D *GetCanvas();
        TAPI void SetTitle(std::string title);
        static inline float c_titleHeight = 25;
    };
}
