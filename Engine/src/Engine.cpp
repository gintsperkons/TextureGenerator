#include "Engine.h"
#include "Core/Window/Window.h"
#include "Core/Renderer/Renderer.h"

TextureGen::Engine::Engine(): Engine(new TextureGen::Window(800, 600, "Engine Window"))
{}

TextureGen::Engine::Engine(Window* starterWindow)
{
	m_window = starterWindow;
	m_renderer = new TextureGen::Renderer();
	m_renderer->InitRenderer(TextureGen::RendererType::Vulkan, m_window->GetWindow());
}

void TextureGen::Engine::Run()
{
		while (!m_window->ShouldClose())
		{
			m_window->PollEvents();
		}
}

TextureGen::Engine::~Engine()
{
		delete m_window;
		delete m_renderer;
}

