#include "OutputConnector.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Renderer/Line.h"

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
    
    m_x += x;
    m_y -= y;
    m_background->Move(x, y);
}

void TextureGenEngine::OutputConnector::Draw()
{
    Component::Draw();
}
