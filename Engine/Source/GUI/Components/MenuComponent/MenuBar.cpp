#include "MenuBar.h"
#include "Core/Renderer/Mesh.h"
#include "Menu.h"

TextureGenEngine::MenuBar::MenuBar():
MenuComponent(25)
{
}

void TextureGenEngine::MenuBar::Init(float width, float height)
{
    MenuComponent::Init(width, height);
    m_y = height - m_height;
    m_background->SetPosition(m_x, m_y);
    m_width = width;

}

void TextureGenEngine::MenuBar::Draw()
{
    MenuComponent::Draw();
    for (auto &menu : m_menus)
    {
        menu->Draw();
    }
}

void TextureGenEngine::MenuBar::Resize(float width, float height)
{
    m_background->Scale(width / (float)m_width, 1);
    m_y = height - m_height;
    m_background->SetPosition(m_x, m_y);
    m_width = width;
    for (auto &menu : m_menus)
    {
        menu->Resize(width, height);
    }

}

void TextureGenEngine::MenuBar::OnHover(float x, float y)
{
    for (auto &menu : m_menus)
    {
        menu->OnHover(x, y);
    }
}

void TextureGenEngine::MenuBar::AddMenu(MenuComponent *menu)
{
    dynamic_cast<Menu *>(menu)->SetMenuBar(m_menus.size() * (float)100, m_y, 100.f, MenuComponent::height);
    m_menus.push_back(menu);
    menu->SetManager(m_manager);
    m_y -= m_height;
    m_background->Scale(1, m_height);
}

TextureGenEngine::MenuBar::~MenuBar()
{
    for (auto &menu : m_menus)
    {
        delete menu;
    }
    m_menus.clear();
}
