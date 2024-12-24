#include "Defines.h"
#include "GUI/Components/Component.h"
#include <vector>

namespace TextureGenEngine
{
    class Connector;
    class OutputConnector : public Component
    {
        Connector * m_connector = nullptr;
        std::vector<Connector *> m_connectors;
        std::string m_type;
    public:
        OutputConnector();
        ~OutputConnector();
        void OnMouseDrag(double x, double y) override;
        void Draw() override;
        void MouseRelease() override;
        void Move(float x, float y) override;
        void ConnectLine(Connector *connector);
        void DisconnectLine(Connector *connector);
        bool ExistConnection(Connector *connector);
        void SetType(std::string type) { m_type = type; }
    };
} // namespace TextureGenEngine