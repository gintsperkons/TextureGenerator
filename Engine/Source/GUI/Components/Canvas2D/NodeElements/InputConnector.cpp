#include "InputConnector.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Renderer/Bezier.h"

TextureGenEngine::InputConnector::InputConnector():
Component(0, 0, 20, 20)
{
    m_background->ChangeColor(1.0f, 1.0f, 0.0f, 1.0f);
    m_type = "InputConnector";
}

void TextureGenEngine::InputConnector::Draw()
{
    Component::Draw();
}

TextureGenEngine::InputConnector::~InputConnector()
{
}

void TextureGenEngine::InputConnector::ConnectLine(Bezier* line)
{
    m_line = line;
    m_line->UpdateEndPosition(m_x, m_y+m_height/2);
}

void TextureGenEngine::InputConnector::Move(float x, float y)
{
    Component::Move(x, y);
    if (m_line)
    {
        m_line->MoveEnd(x,y);
    }
}
