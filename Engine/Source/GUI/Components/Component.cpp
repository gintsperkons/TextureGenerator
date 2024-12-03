#include "Component.h"
#include "Core/Renderer/Mesh.h"
#include "Core/World/ObjectFactory.h"
#include "GUI/GUIManager.h"
#include "Core/Logger/Logger.h"

TextureGenEngine::Component::Component(int x, int y, int width, int height):
m_x(x),m_y(y),m_width(width),m_height(height)
{
    m_background = ObjectFactory::CreateSquare(width, height);
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

void TextureGenEngine::Component::Resize(int width, int height)
{

    float oldWidth, oldHeight;
    m_manager->GetOldSize(oldWidth, oldHeight);
    LOG_DEBUG("Old Width: %f Old Height: %f\n", oldWidth, oldHeight);
    float newWidth = m_width*width/oldWidth;
    float newHeight = m_height*height/oldHeight;
    m_background->Scale(newWidth/m_width, newHeight/m_height);
    m_width = newWidth;
    m_height = newHeight;
}

void TextureGenEngine::Component::SetBackground(Color color)
{
    m_backgroundColor = color;
    m_background->ChangeColor(color.r, color.g, color.b, color.a);
}

void TextureGenEngine::Component::Init(int width, int height)
{
    m_background->SetPosition(m_x, m_y);
    m_background->ChangeColor(m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a);
}
