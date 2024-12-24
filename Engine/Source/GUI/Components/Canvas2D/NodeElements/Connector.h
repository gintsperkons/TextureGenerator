#include "Defines.h"
#include "GUI/Components/Component.h"

namespace TextureGenEngine
{
    class Bezier;
    class InputConnector;
    class OutputConnector;
    class Connector
    {
        Bezier *m_line = nullptr;
        InputConnector *m_input = nullptr;
        OutputConnector *m_output = nullptr;
        std::string m_type;

        bool CheckExistingConnection(InputConnector *input, OutputConnector *output);

    public:
        Connector(std::string type);
        ~Connector();
        void Draw();
        void MakeConnection(OutputConnector *output, InputConnector *input);
        void Disconnect();
        void UpdateEndPosition(float x, float y);
        void UpdateStartPosition(float x, float y);
        void MoveStart(float x, float y);
        void MoveEnd(float x, float y);
    };
} // namespace TextureGenEngine