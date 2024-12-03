#include "MenuComponent.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Logger/Logger.h"

TextureGenEngine::MenuComponent::MenuComponent(int height) : Component(0, 0, 100, height)
{
}

void TextureGenEngine::MenuComponent::Init(int width, int height)
{
    Component::Init(width, height);
    m_y = height-m_height;
    m_background->SetPosition(m_x, m_y);
    m_background->Scale(width/m_width, 1);
}

void TextureGenEngine::MenuComponent::Draw()
{
    Component::Draw();
}

void TextureGenEngine::MenuComponent::Resize(int width, int height)
{   LOG_DEBUG("X: %d Y: %d W: %d H: %d\n", m_x, m_y, m_width, m_height);
    LOG_DEBUG("Resizing MenuComponent to %d %d\n", width / m_width, height);
    m_background->Scale(width/(float)m_width, 1);
    m_y = height-m_height;
    m_background->SetPosition(m_x, m_y);
    m_width = width;
}

TextureGenEngine::MenuComponent::~MenuComponent()
{
}
