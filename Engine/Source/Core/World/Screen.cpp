#include "Screen.h"
#include "Core/Input/Input.h"
#include "Core/Input/MouseCodes.h"
#include "Core/Logger/Logger.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Renderer/Mesh.h"
#include <Engine.h>
#include <Core/Window/Window.h>
#include "Core/GUI/GUIManager.h"
#include "Core/Renderer/Text.h"

TextureGenEngine::Screen::Screen()
{
   m_mesh = ObjectFactory::CreateSquare();
   m_textMesh = new Text();
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
    //m_mesh->Draw();
    m_textMesh->Draw("Hello World", 25.0f, 25.0f, 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    
}

void TextureGenEngine::Screen::SetGUIManager(GUIManager* guiManager)
{
    m_guiManager = guiManager;
}

TextureGenEngine::Screen::~Screen()
{
    delete m_mesh;
    delete m_textMesh;
}
