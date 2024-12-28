#include "Menu.h"
#include "Core/Renderer/Text.h"
#include "Core/Logger/Logger.h"
#include "Core/Renderer/Mesh.h"

TextureGenEngine::Menu::Menu(std::string title):m_title(title),
MenuComponent(MenuComponent::height)
{
    m_text = new Text();
}


void TextureGenEngine::Menu::Draw()
{
        MenuComponent::Draw();
        m_text->Draw(m_title, m_x, m_y, (int)m_height, (int)m_width, 12, AlignmentHorizontal::LEFT, AlignmentVertical::CENTER);
}

void TextureGenEngine::Menu::Resize(float width, float height)
{
    m_y = height - m_height;
    m_background->SetPosition(m_x, m_y);
    m_width = width;
}

void TextureGenEngine::Menu::SetMenuBar(float x, float y, float width, float height)
{
    m_x = x;
    m_y = y;
    m_background->Scale(width/m_width, 1);
    m_width = width;
    m_height = height;
    m_background->SetPosition(m_x, MenuComponent::height);
}

TextureGenEngine::Menu::~Menu()
{
    delete m_text;
}
