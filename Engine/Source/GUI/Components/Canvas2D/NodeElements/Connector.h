#pragma once
#include "Defines.h"
#include "GUI/Components/Component.h"
#include "GUI/Color.h"
#include <map>
#include <string>

namespace TextureGenEngine
{
    inline std::map<std::string, Color> m_colors = {
        {"text", Color(1.0f, 1.0f, 0.0f, 1.0f)},          // White for Text input
        {"integer", Color(0.290f, 0.565f, 0.886f, 1.0f)}, // Sky Blue for Integer input
        {"float", Color(0.157f, 0.654f, 0.267f, 1.0f)},   // Green for Floating-point input
        {"image", Color(1.0f, 0.549f, 0.0f, 1.0f)}        // Orange for Image input
    };
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