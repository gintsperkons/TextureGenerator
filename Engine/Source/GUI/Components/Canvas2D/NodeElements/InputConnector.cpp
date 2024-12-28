#include "InputConnector.h"
#include "Core/Renderer/Mesh.h"
#include "GUI/GUIManager.h"
#include "Core/Logger/Logger.h"
#include "GUI/Components/Canvas2D/Node.h"
#include "GUI/Components/Canvas2D/Canvas2D.h"
#include "Core/AssetManager/AssetManager.h"
#include "Core/Renderer/Texture.h"
#include "NodeElement.h"
#include "Connector.h"

TextureGenEngine::InputConnector::InputConnector() : Component(0, 0, 20, 20)
{
    m_background->ChangeColor(1.0f, 0.0f, 0.0f, 1.0f);
    m_type = "InputConnector";
    Texture *texture = TextureGenEngine::LoadTexture("Connector.png");
    m_background->ChangeShader("maskedColor");
    m_background->ChangeTexture(texture);
}

bool TextureGenEngine::InputConnector::ExistConnection(Connector *connector)
{
    return m_connector == connector;
}

void TextureGenEngine::InputConnector::Draw()
{
    Component::Draw();
    if (m_tempConnection != nullptr)
    {
        m_tempConnection->Draw();
    }
}

TextureGenEngine::InputConnector::~InputConnector()
{
    if (m_tempConnection != nullptr)
    {
        delete m_tempConnection;
        m_tempConnection = nullptr;
    }
    m_connector = nullptr;
}

void TextureGenEngine::InputConnector::OnMouseDrag(float x, float y)
{
    // SpawnConnectorLine();
    if (m_tempConnection == nullptr)
    {
        LOG_DEBUG("Creating line\n");
        LOG_DEBUG("x %f y %f\n", m_x, m_y);
        m_tempConnection = new Connector("text");
        m_tempConnection->UpdateEndPosition(m_x, m_y + m_height / 2);
    }
    if (m_manager == nullptr)
    {
        LOG_ERROR("Manager is null\n");
        return;
    }
    float posX, posY;
    m_manager->GetMousePosition(posX, posY);
    m_tempConnection->UpdateStartPosition(posX, posY);
}

void TextureGenEngine::InputConnector::MouseRelease()
{
    float posX, posY;
    m_manager->GetMousePosition(posX, posY);
    if (m_tempConnection == nullptr)
        return;

    if (dynamic_cast<NodeElement *>(m_parent) == nullptr)
    {
        if (m_parent == nullptr)
        {
            LOG_ERROR("Parent is null\n");
        }
        else
            LOG_ERROR("Parent is not a NodeElement\n");
        return;
    }
    OutputConnector *output = static_cast<Node *>(static_cast<NodeElement *>(m_parent)->GetNode())->GetCanvas()->GetOutputConnector(posX, posY);
    if (output != nullptr)
    {
        m_connector = m_tempConnection;
        m_tempConnection = nullptr;
        m_connector->MakeConnection(output, this);
    }
    else
    {
        delete m_tempConnection;
    }
    if (m_tempConnection != nullptr)
    {
        m_tempConnection = nullptr;
    }
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

void TextureGenEngine::InputConnector::SetType(std::string type)
{
    m_type = type;
    if (m_colors.find(type) != m_colors.end())
    {
        m_background->ChangeColor(m_colors[type].r, m_colors[type].g, m_colors[type].b, m_colors[type].a);
    }
    else
        m_background->ChangeColor(1.0f, 1.0f, 1.0f, 1.0f);
}
