#include "Component.h"
#include "Core/Renderer/Mesh.h"
#include "Core/World/ObjectFactory.h"

TextureGenEngine::Component::Component(int x, int y, int width, int height):
m_x(x),m_y(y),m_width(width),m_height(height)
{
    m_background = ObjectFactory::CreateSquare(width, height);
    m_backgroundColor.r = 1.0f;
    m_backgroundColor.g = 0.0f;
    m_backgroundColor.b = 0.0f;
    m_backgroundColor.a = 1.0f;
    m_background->ChangeColor(m_backgroundColor.r,m_backgroundColor.g,m_backgroundColor.b,m_backgroundColor.a);
    m_background->SetPosition(x,y);
}

void TextureGenEngine::Component::Draw()
{
    if (m_background)
    {
        m_background->Draw();
    }
}

TextureGenEngine::Component::~Component()
{
}

void TextureGenEngine::Component::SetBackground(Color color)
{
    m_backgroundColor = color;
    m_background->ChangeColor(color.r, color.g, color.b, color.a);
}
