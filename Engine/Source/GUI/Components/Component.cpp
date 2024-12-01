#include "Component.h"
#include "Core/Renderer/Mesh.h"
#include "Core/World/ObjectFactory.h"

TextureGenEngine::Component::Component(int x, int y, int width, int height)
{
    m_background = ObjectFactory::CreateSquare(width, height);
    m_backgroundColor[0] = 1.0f;
    m_backgroundColor[1] = 0.0f;
    m_backgroundColor[2] = 0.0f;
    m_backgroundColor[3] = 1.0f;
    m_background->ChangeColor(m_backgroundColor[0],m_backgroundColor[1],m_backgroundColor[2],m_backgroundColor[3]);
}

void TextureGenEngine::Component::Draw()
{
    if (m_background)
    {
        m_background->Draw();
    }
}

TextureGenEngine::Component::~Component()
{
}
