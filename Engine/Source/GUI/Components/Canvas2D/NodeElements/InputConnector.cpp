#include "InputConnector.h"
#include "Core/Renderer/Mesh.h"
#include "Connector.h"

TextureGenEngine::InputConnector::InputConnector() : Component(0, 0, 20, 20)
{
    m_background->ChangeColor(1.0f, 1.0f, 0.0f, 1.0f);
    m_type = "InputConnector";
}

bool TextureGenEngine::InputConnector::ExistConnection(Connector *connector)
{
    return m_connector == connector;
}

void TextureGenEngine::InputConnector::Draw()
{
    Component::Draw();
}

TextureGenEngine::InputConnector::~InputConnector()
{
}

void TextureGenEngine::InputConnector::ConnectLine(Connector *connector)
{
    m_connector = connector;
    m_connector->UpdateEndPosition(m_x, m_y + m_height / 2);
}

void TextureGenEngine::InputConnector::DisconnectLine()
{
    m_connector = nullptr;
}

void TextureGenEngine::InputConnector::Move(float x, float y)
{
    Component::Move(x, y);
    if (m_connector)
    {
        m_connector->MoveEnd(x, y);
    }
}
