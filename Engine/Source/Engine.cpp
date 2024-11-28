#include "Engine.h"
#include <stdio.h>
#include "Core/Renderer/Mesh.h"
#include "Core/Window/WindowManager.h"
#include "Core/Logger/Logger.h"
#include "Core/Window/Window.h"
#include "Core/Asserts.h"

void TextureGenEngine::Engine::Init()
{
	g_engine = new Engine();
}

void TextureGenEngine::Engine::Shutdown()
{
	delete g_engine;
	g_engine = nullptr;
}

TextureGenEngine::Window* TextureGenEngine::Engine::AddWindow(const std::string &title, int width, int height)
{
	return m_windowManager->AddWindow(title, width, height);
}

TextureGenEngine::Engine::Engine() : m_windowManager(new WindowManager())
{
	m_running = true;
}

TextureGenEngine::Engine::~Engine()
{
}

void TextureGenEngine::Engine::Run()
{
	m_windowManager->Update();
	m_running = !m_windowManager->ShouldClose();
}

TextureGenEngine::Engine *TextureGenEngine::Engine::Get()
{
	return g_engine;
}

bool TextureGenEngine::Engine::IsRunning()
{
	return m_running;
}

