#include "Engine.h"
#include "Core/Window/Window.h"
#include "Core/Renderer/Renderer.h"

TextureGen::Engine::Engine()
{
		m_window = new TextureGen::Window(800, 600, "My Lovely Window");
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

