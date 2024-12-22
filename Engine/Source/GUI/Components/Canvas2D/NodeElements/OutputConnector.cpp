#include "OutputConnector.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Renderer/Bezier.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Logger/Logger.h"
#include "GUI/GUIManager.h"
#include "NodeElement.h"
#include "GUI/Components/Canvas2D/Node.h"
#include "GUI/Components/Canvas2D/Canvas2D.h"
#include "InputConnector.h"

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

void TextureGenEngine::OutputConnector::OnMouseDrag(double x, double y)
{
    // SpawnConnectorLine();
    if (m_line == nullptr)
    {
        LOG_DEBUG("Creating line\n");
        LOG_DEBUG("x %f y %f\n", m_x, m_y);
        m_line = ObjectFactory::CreateBezier(m_x+m_width, m_y+m_height/2, m_x+100, m_y+100, 100);
        m_line->ChangeColor(1.0f, 0.0f, 1.0f, 1.0f);
        m_lines.push_back(m_line);
    }
    if (m_manager == nullptr)
    {
        LOG_ERROR("Manager is null\n");
        return;
    }
    float posX, posY;
    m_manager->GetMousePosition(posX, posY);
    m_line->UpdateEndPosition(posX, posY);
}

void TextureGenEngine::OutputConnector::Draw()
{
    Component::Draw();
    for (auto &line : m_lines)
    {
        line->Draw();
    }
}

void TextureGenEngine::OutputConnector::MouseRelease()
{
    float posX, posY;
    m_manager->GetMousePosition(posX, posY);
    m_line->UpdateEndPosition(posX, posY);

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
        input->ConnectLine(m_line);
    }
    else
    {

        m_lines.pop_back();
        delete m_line;
    }
    if (m_line != nullptr)
    {
        m_line = nullptr;
    }
}

void TextureGenEngine::OutputConnector::Move(float x, float y)
{
    Component::Move(x, y);
    for (auto &line : m_lines)
    {
        line->MoveStart(x, y);
    }
}
