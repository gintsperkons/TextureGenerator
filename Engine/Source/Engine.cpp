#include "Engine.h"
#include <stdio.h>
#include "Core/Window/Window.h"
#include "Core/Renderer/Mesh.h"

TextureGenEngine::Engine::Engine():Engine(new Window())
{
}

TextureGenEngine::Engine::Engine(Window* window):m_window(window),m_mesh(new Mesh())
{
}

TextureGenEngine::Engine::~Engine()
{
	delete m_window;
}

void TextureGenEngine::Engine::Run()
{
	while (!m_window->ShouldClose())
	{
		m_window->Update();
		m_mesh->Draw();

	}
}
