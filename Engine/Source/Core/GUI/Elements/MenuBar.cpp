#include "MenuBar.h"
#include "Core/Renderer/Mesh.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Logger/Logger.h"
#include "Engine.h"
#include "Core/Window/Window.h"

TextureGenEngine::MenuBar::MenuBar()
    : BaseElement(0, TextureGenEngine::Engine::Get()->GetWindow()->GetHeight()-m_menuBarHeight, TextureGenEngine::Engine::Get()->GetWindow()->GetWidth(), m_menuBarHeight)
{
    lockWidth = false;
    m_mesh = ObjectFactory::CreateSquare(m_x, m_y, m_width, m_height);
}

void TextureGenEngine::MenuBar::Draw()
{
    m_mesh->Draw();
}

TextureGenEngine::MenuBar::~MenuBar()
{

}
