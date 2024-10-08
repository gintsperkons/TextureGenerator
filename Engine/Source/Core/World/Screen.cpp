#include "Screen.h"
#include "Core/Input/Input.h"
#include "Core/Input/MouseCodes.h"
#include "Core/Logger/Logger.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Renderer/Mesh.h"
#include <Engine.h>
#include <Core/Window/Window.h>

TextureGenEngine::Screen::Screen()
{
    m_mesh = ObjectFactory::CreateSquare();
}

void TextureGenEngine::Screen::Update()
{
    if (Input::MouseButtonPressed(Mouse::ButtonLeft))
    {
        LOG_INFO("Left Mouse Button Pressed screen\n");
        int width, height;
        TextureGenEngine::Engine::Get()->GetWindow()->GetFramebufferSize(width, height);
        int* size = Input::GetMousePosition();
        LOG_DEBUG("Screen Size: %d, %d\n", width, height);
        LOG_DEBUG("Mouse Position: %d, %d\n", size[0], size[1]);
        float x = ((float)size[0] / (float)width)*2 -1;
        float y= ((float)size[1] / (float)height) * 2 - 1;
        m_mesh->CheckClickColision(x,y);
        
    }
}

void TextureGenEngine::Screen::Draw()
{
    m_mesh->Draw();
}



TextureGenEngine::Screen::~Screen()
{
}
