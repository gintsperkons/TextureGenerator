#include "MenuBar.h"
#include "Core/Renderer/Mesh.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Logger/Logger.h"

TextureGenEngine::MenuBar::MenuBar()
:BaseElement(0, 200, 800, 50)
{
    m_mesh = ObjectFactory::CreateSquare(m_x, m_y, m_width, m_height);
}

void TextureGenEngine::MenuBar::Draw()
{
    m_mesh->Draw();
}

TextureGenEngine::MenuBar::~MenuBar()
{

}
