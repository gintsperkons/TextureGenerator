#include "InputConnector.h"
#include "Core/Renderer/Mesh.h"

TextureGenEngine::InputConnector::InputConnector():
Component(0, 0, 20, 20)
{
    m_background->ChangeColor(1.0f, 1.0f, 0.0f, 1.0f);
    m_type = "InputConnector";
}

TextureGenEngine::InputConnector::~InputConnector()
{
}
