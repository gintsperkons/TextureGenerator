#include "Defines.h"
#include "GUI/Components/Component.h"
#include "NodeTypes.h"
#include <vector>
#include <functional>

namespace TextureGenEngine
{
    class Connector;
    class TextureData;
    class OutputConnector : public Component
    {
        std::function<void()> m_onUpdate = nullptr;
        Connector *m_connector = nullptr;
        std::vector<Connector *> m_connectors;
        std::string m_type;
        NodeDataTypes m_dataType;

    public:
        TAPI OutputConnector();
        ~OutputConnector();
        void OnMouseDrag(float x, float y) override;
        void Draw() override;
        void MouseRelease() override;
        void Move(float x, float y) override;
        void ConnectLine(Connector *connector);
        void DisconnectLine(Connector *connector);
        bool ExistConnection(Connector *connector);
        std::string GetConnectionUUIDs();
        NodeDataTypes GetDataType() { return m_dataType; }
        void TAPI SetDataType(NodeDataTypes type);
        void TAPI UpdateData(std::string data);
        void TAPI UpdateData(int data);
        void TAPI UpdateData(float data);
        void TAPI UpdateData(TextureData* data);
        void TAPI SetOnUpdate(std::function<void()> onUpdate);
        void TAPI TriggerUpdate();
    };
} // namespace TextureGenEngine