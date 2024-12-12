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
    m_text->Draw(m_title, m_x, m_y, m_height, m_width, 12, glm::vec3(0.0f, 0.0f, 0.0f), AlignmentHorizontal::LEFT, AlignmentVertical::CENTER);
}

void TextureGenEngine::Menu::Resize(int width, int height)
{
    m_y = height - m_height;
    m_background->SetPosition(m_x, m_y);
    m_width = width;
}

void TextureGenEngine::Menu::SetMenuBar(int x, int y, int width, int height)
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
}
