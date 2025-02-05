#pragma once
#include "Defines.h"
#include "GUI/Components/Component.h"
#include "NodeTypes.h"
#include "GUI/Color.h"
#include "NodeTypes.h"
#include <map>
#include <string>

namespace TextureGenEngine
{


    inline std::map<NodeDataTypes, Color> m_colors = {
        {NodeDataTypes::NONE, Color(1.0f, 1.0f, 1.0f, 1.0f)},          // Red for No type
        {NodeDataTypes::TEXT, Color(1.0f, 1.0f, 0.0f, 1.0f)},          // White for Text input
        {NodeDataTypes::INTEGER, Color(0.290f, 0.565f, 0.886f, 1.0f)}, // Sky Blue for Integer input
        {NodeDataTypes::FLOAT, Color(0.157f, 0.654f, 0.267f, 1.0f)},   // Green for Floating-point input
        {NodeDataTypes::IMAGE, Color(1.0f, 0.549f, 0.0f, 1.0f)},      // Orange for Image input
        {NodeDataTypes::PATTERNGENERATOR, Color(0.0f, 0.1f, 1.0f, 1.0f)}      // Blue for Pattern Generator
    };
    class Bezier;
    class InputConnector;
    class OutputConnector;
    class Connector
    {
        Bezier *m_line = nullptr;
        InputConnector *m_input = nullptr;
        OutputConnector *m_output = nullptr;
        NodeDataTypes m_type;

        bool CheckExistingConnection(InputConnector *input, OutputConnector *output);

    public:
        Connector(NodeDataTypes type);
        ~Connector();
        void Draw();
        void MakeConnection(OutputConnector *output, InputConnector *input);
        void Disconnect();
        void UpdateEndPosition(float x, float y);
        void UpdateStartPosition(float x, float y);
        void MoveStart(float x, float y);
        void MoveEnd(float x, float y);
        std::string GetConnectionUUIDs();
        void UpdateData(std::string data);
        void UpdateData(int data);  
        void UpdateData(float data);
        void UpdateData(std::vector<PatternGeneratorData> data);
    };
} // namespace TextureGenEngine