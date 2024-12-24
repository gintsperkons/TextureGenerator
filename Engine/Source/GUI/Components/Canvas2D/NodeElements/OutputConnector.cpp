#include "OutputConnector.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Renderer/Bezier.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Logger/Logger.h"
#include "GUI/GUIManager.h"
#include "NodeElement.h"
#include "GUI/Components/Canvas2D/Node.h"
#include "GUI/Components/Canvas2D/Canvas2D.h"
#include "Connector.h"

TextureGenEngine::OutputConnector::OutputConnector() : Component(0, 0, 20, 20)
{
    m_background->ChangeColor(1.0f, 0.0f, 1.0f, 1.0f);
    m_selectable = true;
    m_draggable = true;
    m_type = "OutputConnector";
}

TextureGenEngine::OutputConnector::~OutputConnector()
{
}

void TextureGenEngine::OutputConnector::OnMouseDrag(float x, float y)
{
    // SpawnConnectorLine();
    if (m_connector == nullptr)
    {
        LOG_DEBUG("Creating line\n");
        LOG_DEBUG("x %f y %f\n", m_x, m_y);
        m_connector = new Connector("text");
        m_connector->UpdateStartPosition(m_x+m_width, m_y + m_height / 2);
        m_connectors.push_back(m_connector);
    }
    if (m_manager == nullptr)
    {
        LOG_ERROR("Manager is null\n");
        return;
    }
    float posX, posY;
    m_manager->GetMousePosition(posX, posY);
    m_connector->UpdateEndPosition(posX, posY);
}

void TextureGenEngine::OutputConnector::Draw()
{
    Component::Draw();
    for (auto &line : m_connectors)
    {
        line->Draw();
    }
}

void TextureGenEngine::OutputConnector::MouseRelease()
{
    float posX, posY;
    m_manager->GetMousePosition(posX, posY);
    if (m_connector == nullptr) return;

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
    InputConnector *input = static_cast<Node *>(static_cast<NodeElement *>(m_parent)->GetNode())->GetCanvas()->GetInputConnector(posX, posY);
    if (input != nullptr)
    {
        m_connector->MakeConnection(this, input);
    }
    else
    {

        m_connectors.pop_back();
        delete m_connector;
    }
    if (m_connector != nullptr)
    {
        m_connector = nullptr;
    }
}

void TextureGenEngine::OutputConnector::Move(float x, float y)
{
    Component::Move(x, y);
    for (auto &line : m_connectors)
    {
        line->MoveStart(x, y);
    }
}

void TextureGenEngine::OutputConnector::ConnectLine(Connector *connector)
{
    connector->UpdateStartPosition(m_x + m_width, m_y + m_height / 2);
    if (connector != m_connector){
        m_connectors.push_back(connector);
    }
}

void TextureGenEngine::OutputConnector::DisconnectLine(Connector *connector)
{
    if (m_connector == connector)
    {
        m_connector = nullptr;
    }
    for (auto it = m_connectors.begin(); it != m_connectors.end(); ++it)
    {
        if (*it == connector)
        {
            m_connectors.erase(it);
            break;
        }
    }
}

bool TextureGenEngine::OutputConnector::ExistConnection(Connector *connector)
{
	if (m_connectors.empty())
	{
		return false;
	}
    for (auto &line : m_connectors)
    {
        if (line == connector)
        {
            return true;
        }
    }
    return false;
}
