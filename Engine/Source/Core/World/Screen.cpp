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
    m_textMesh = new Text();
}

void TextureGenEngine::Screen::Update()
{
    if (Input::MouseButtonPressed(Mouse::ButtonLeft))
    {
        int width, height;
        TextureGenEngine::Engine::Get()->GetWindow()->GetFramebufferSize(width, height);
        int *size = Input::GetMousePosition();
        if (m_guiManager)
            m_guiManager->Click(size[0], size[1]);
    }
    if (Input::MouseButtonHeld(Mouse::ButtonLeft))
    {
        int width, height;
        TextureGenEngine::Engine::Get()->GetWindow()->GetFramebufferSize(width, height);
        int *size = Input::GetMousePosition();
        double *mouseDelta = Input::GetMouseDelta();
        if (m_isDragging)
        {
            if (m_guiManager)
                m_guiManager->Drag(mouseDelta[0], mouseDelta[1]);
        }
        else if (m_guiManager)
            m_guiManager->GetDraggable(size[0], size[1]);
            m_isDragging = true;
    }
    if (Input::MouseButtonReleased(Mouse::ButtonLeft))
    {
        m_isDragging = false;
    }
}

void TextureGenEngine::Screen::Draw()
{
    m_guiManager->Draw();
}

void TextureGenEngine::Screen::SetGUIManager(GUIManager *guiManager)
{
    m_guiManager = guiManager;
}

TextureGenEngine::Screen::~Screen()
{
    delete m_textMesh;
}

void TextureGenEngine::Screen::Resize(int width, int height)
{
    m_guiManager->Resize(width, height);
}
