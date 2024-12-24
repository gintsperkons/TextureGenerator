#include "MenuComponent.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Logger/Logger.h"

TextureGenEngine::MenuComponent::MenuComponent(float height) : Component(0, 0, 100, height)
{
}

void TextureGenEngine::MenuComponent::Init(float width, float height)
{
    Component::Init(width, height);
    m_y = height - m_height;
    m_background->SetPosition(m_x, m_y);
    Resize(width, height);
}

void TextureGenEngine::MenuComponent::Draw()
{
    Component::Draw();
}

void TextureGenEngine::MenuComponent::Resize(float width, float height)
{
    m_y = height - m_height;
    m_background->SetPosition(m_x, m_y);
    m_width = width;
}

TextureGenEngine::MenuComponent::~MenuComponent()
{
}
