#include "MenuBar.h"
#include "Core/Renderer/Mesh.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Logger/Logger.h"
#include "Engine.h"
#include "Core/Window/Window.h"
#include "Core/GUI/Elements/Menu.h"



TextureGenEngine::MenuBar::MenuBar()
    : BaseElement(0, TextureGenEngine::Engine::Get()->GetWindow()->GetHeight() - m_menuBarHeight, TextureGenEngine::Engine::Get()->GetWindow()->GetWidth(), m_menuBarHeight)
{
    m_alignTop = true;
    m_canClick = false;
    m_scaleWidth = true;
    m_mesh = ObjectFactory::CreateSquare(m_width, m_height);
    m_mesh->SetPosition(m_x, m_y);
    m_mesh->ChangeColor(0.1f, 0.1f, 0.1f, 1.0f);

}

void TextureGenEngine::MenuBar::Draw()
{
    if (m_mesh != nullptr)
        m_mesh->Draw();
    for (BaseElement *child : m_children)
    {
        if (child != nullptr)
            child->Draw();
    }
}

void TextureGenEngine::MenuBar::AddMenu(Menu *menu)
{
    menu->UpdatePosition(m_children.size() * 100);
    AddChild((BaseElement*)(menu));

}

TextureGenEngine::MenuBar::~MenuBar()
{

}
