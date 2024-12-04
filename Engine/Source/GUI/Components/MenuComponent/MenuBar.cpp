#include "MenuBar.h"
#include "Core/Renderer/Mesh.h"
#include "Menu.h"

TextureGenEngine::MenuBar::MenuBar():
MenuComponent(25)
{
}

void TextureGenEngine::MenuBar::Init(int width, int height)
{
    MenuComponent::Init(width, height);
    m_y = height - m_height;
    m_background->SetPosition(m_x, m_y);
    m_width = width;
    for (auto &menu : m_menus)
    {
        menu->Init(width, height);
    }
}

void TextureGenEngine::MenuBar::Draw()
{
    MenuComponent::Draw();
    for (auto &menu : m_menus)
    {
        menu->Draw();
    }
}

void TextureGenEngine::MenuBar::Resize(int width, int height)
{
    m_background->Scale(width / (float)m_width, 1);
    m_y = height - m_height;
    m_background->SetPosition(m_x, m_y);
    m_width = width;

}

void TextureGenEngine::MenuBar::AddMenu(MenuComponent *menu)
{
    dynamic_cast<Menu*>(menu)->SetMenuBar(m_menus.size() * 100, m_y, 100, MenuComponent::height);
    m_menus.push_back(menu);
    menu->SetManager(m_manager);
    menu->Init(m_width, m_height);
    m_y -= m_height;
    m_background->Scale(1, m_height);
}

TextureGenEngine::MenuBar::~MenuBar()
{
}
