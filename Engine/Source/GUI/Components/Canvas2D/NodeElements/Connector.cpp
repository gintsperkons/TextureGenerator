#include "Connector.h"
#include "Core/Renderer/Bezier.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Logger/Logger.h"
#include "InputConnector.h"
#include "OutputConnector.h"

bool TextureGenEngine::Connector::CheckExistingConnection(InputConnector *input, OutputConnector *output)
{
    if (output->ExistConnection(input->GetConnection()))
    {
        return true;
    }
    return false;
}

TextureGenEngine::Connector::Connector(NodeDataTypes type)
{
    m_type = type;
    m_line = ObjectFactory::CreateBezier(100, 100, 200, 200);
    if (m_colors.find(type) != m_colors.end())
    {
        Color color = m_colors[type];
        m_line->ChangeColor(color.r, color.g, color.b, color.a);
        LOG_DEBUG("Color %f %f %f %f\n", color.r, color.g, color.b, color.a);
    }
    else
        m_line->ChangeColor(1.0f, 1.0f, 1.0f, 1.0f);
}

TextureGenEngine::Connector::~Connector()
{
    if (m_line != nullptr)
        delete m_line;
    m_line = nullptr;
}

void TextureGenEngine::Connector::Draw()
{
    if (m_line)
    {
        m_line->Draw();
    }
}

void TextureGenEngine::Connector::MakeConnection(OutputConnector *output, InputConnector *input)
{
    m_input = input;
    m_output = output;
    if (CheckExistingConnection(input, output))
    {
        if (input->GetConnection() != nullptr)
            input->GetConnection()->Disconnect();
        Disconnect();
        return;
    }
    output->ConnectLine(this);
    input->ConnectLine(this);
}

void TextureGenEngine::Connector::Disconnect()
{
    if (m_input)
    {
        m_input->DisconnectLine();
    }
    if (m_output)
    {
        m_output->DisconnectLine(this);
    }
    delete this;
}

void TextureGenEngine::Connector::UpdateEndPosition(float x, float y)
{
    m_line->UpdateEndPosition(x, y);
}

void TextureGenEngine::Connector::UpdateStartPosition(float x, float y)
{
    m_line->UpdateStartPosition(x, y);
}

void TextureGenEngine::Connector::MoveStart(float x, float y)
{
    m_line->MoveStart(x, y);
}

void TextureGenEngine::Connector::MoveEnd(float x, float y)
{
    m_line->MoveEnd(x, y);
}
