#include "OutputConnector.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Renderer/Line.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Logger/Logger.h"
#include "GUI/GUIManager.h"

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
    //SpawnConnectorLine();
    if (m_line == nullptr)
    {   LOG_DEBUG("Creating line\n");
    LOG_DEBUG("x %f y %f\n", m_x, m_y);
        m_line = ObjectFactory::CreateLine(m_x+m_width, m_y+m_height/2, m_x + 100, m_y - 100);
        m_line->ChangeColor(1.0f, 0.0f, 1.0f, 1.0f);
        m_lines.push_back(m_line);
    }
    if (m_manager == nullptr)
    {
        LOG_ERROR("Manager is null\n");
        return;
    }
    float posX,posY;
        m_manager->GetMousePosition(posX,posY);
    m_line->UpdateEndPosition(posX, posY);
}

void TextureGenEngine::OutputConnector::Draw()
{
    Component::Draw();
    for (auto &line : m_lines)
    {   
        LOG_DEBUG("Drawing line\n");
        line->Draw();
    }
}

void TextureGenEngine::OutputConnector::MouseRelease()
{
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
