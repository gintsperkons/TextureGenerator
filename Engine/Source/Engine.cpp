#include "Engine.h"
#include <stdio.h>
#include "Core/Window/Window.h"
#include "Core/Renderer/Mesh.h"

#include "Core/Window/WindowEvents.h"

TextureGenEngine::Engine::Engine():Engine(new Window())
{
}

void TextureGenEngine::Engine::ResizeCallBack(ResizeEvent event) {
	printf("Resize event: %d, %d\n", event.width, event.height);

	m_window->Update();
	m_window->Draw();

}


TextureGenEngine::Engine::Engine(Window* window):m_window(window)
{
	m_window->AddResizeListener([this](ResizeEvent event) { this->ResizeCallBack(event); });
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
		m_window->Draw();

	}
}
