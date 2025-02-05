#include "Defines.h"
#include "GUI/Components/Component.h"
#include "NodeTypes.h"
#include <string>

namespace TextureGenEngine
{
    class Connector;
    class Texture;
    class InputConnector : public Component
    {
        Connector *m_tempConnection = nullptr;
        Connector *m_connector = nullptr;
        std::string m_type;
        NodeDataTypes m_dataType;

    public:
        InputConnector();
        bool ExistConnection(Connector *connector);
        void Draw() override;
        ~InputConnector();
        void OnMouseDrag(float x, float y) override;
        void MouseRelease() override;
        void ConnectLine(Connector *connector);
        void DisconnectLine();
        TextureGenEngine::Connector *GetConnection() { return m_connector; }
        void Move(float x, float y) override;
        void LockInput();
        void UnlockInput();
        std::string GetConnectionUUID();
        TAPI void SetDataType(NodeDataTypes type);
        void UpdateData(std::string data);
        void UpdateData(int data);
        void UpdateData(float data);
        void UpdateData(std::vector<PatternGeneratorData> data);
    }; // namespace TextureGenEngine
}