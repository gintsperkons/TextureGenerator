#include "Engine.h"
#include <stdio.h>
#include "Core/Window/Window.h"
#include "Core/Renderer/Mesh.h"
#include "Core/World/Screen.h"
#include "Core/Window/WindowEvents.h"
#include "Core/FontManager.h"
#include "Core/Logger/Logger.h"
#include "Core/Asserts.h"

TextureGenEngine::Engine::Engine():Engine(new Window())
{
}

void TextureGenEngine::Engine::ResizeCallBack(ResizeEvent event) {

	m_screen->Update();
	m_window->Update();
	m_window->Draw();
	m_screen->Draw();

}


TextureGenEngine::Engine::Engine(Window* window):m_window(window)
{
	TextureGenEngine::g_engine = this;
	m_window->AddResizeListener([this](ResizeEvent event) { this->ResizeCallBack(event); });
	m_screen = new Screen();
	m_fontManager = new FontManager();
}

TextureGenEngine::Engine::~Engine()
{
	delete m_window;
	delete m_screen;
}

void TextureGenEngine::Engine::Run()
{
		m_screen->Update();
		m_window->Update();
		m_window->Draw();
		m_screen->Draw();
}

TextureGenEngine::Window* TextureGenEngine::Engine::GetWindow()
{
	return m_window;
}

TextureGenEngine::Renderer *TextureGenEngine::Engine::GetRenderer()
{
	if (!GetWindow()->GetRenderer())
	{
		LOG_ERROR("renderer is null");
	}
	return GetWindow()->GetRenderer();
}

TextureGenEngine::Screen* TextureGenEngine::Engine::GetScreen()
{
	return m_screen;
}

TextureGenEngine::Engine* TextureGenEngine::Engine::Get()
{
	return g_engine;
}

TAPI bool TextureGenEngine::Engine::IsRunning()
{
	return !m_window->ShouldClose();
}
