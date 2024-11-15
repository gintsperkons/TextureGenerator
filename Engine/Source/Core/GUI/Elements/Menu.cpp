#include "Menu.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Logger/Logger.h"
#include "Core/Renderer/Text.h"
#include "Engine.h"
#include "Core/Window/Window.h"
#include "Core/World/ObjectFactory.h"

TextureGenEngine::Menu::Menu(std::string title)
    : BaseElement(0, TextureGenEngine::Engine::Get()->GetWindow()->GetHeight() - m_menuBarHeight, 100, m_menuBarHeight), m_title(title)
{
    LOG_DEBUG("Size: %d, %d\n", m_width, m_height);
    m_mesh = ObjectFactory::CreateSquare(m_x, m_y, m_width, m_height);
    m_mesh->ChangeColor(0.0f, 0.0f, 1.0f, 0.0f);
    m_text = new Text();
}

void TextureGenEngine::Menu::Draw()
{
    if (m_mesh != nullptr)
        m_mesh->Draw();
    for (BaseElement *child : m_children)
    {
        if (child != nullptr)
            child->Draw();
    }
    m_text->Draw(m_title, m_x, m_y, m_height/50.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}

TextureGenEngine::Menu::~Menu()
{
}
