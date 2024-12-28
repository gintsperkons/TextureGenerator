#include "Engine.h"
#include <stdio.h>
#include "Core/Renderer/Mesh.h"
#include "Core/Window/WindowManager.h"
#include "Core/Logger/Logger.h"
#include "Core/Window/Window.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Font/FontManager.h"
#include "Core/Asserts.h"
#include "Core/AssetManager/AssetManager.h"

void TextureGenEngine::Engine::Init()
{
	g_engine = new Engine();
}

void TextureGenEngine::Engine::Shutdown()
{
	delete g_engine;
	g_engine = nullptr;
}

TextureGenEngine::Window *TextureGenEngine::Engine::AddWindow(const std::string &title, int width, int height)
{
	return m_windowManager->AddWindow(title, width, height);
}

TextureGenEngine::Window *TextureGenEngine::Engine::GetMainWindow()
{
	return m_windowManager->GetMainWindow();
}

double TextureGenEngine::Engine::GetTime()
{
	return m_windowManager->GetTime();
}

TextureGenEngine::Engine::Engine() : 
m_windowManager(new WindowManager()),
m_renderer(new Renderer(m_windowManager->GetMainWindow()->GetWidth(), m_windowManager->GetMainWindow()->GetHeight())),
m_fontManager(new FontManager()),
m_assetManager(new AssetManager()),
m_running(true)
{
}

TextureGenEngine::Engine::~Engine()
{
	m_running = false;
	if (m_assetManager)
		delete m_assetManager;
	m_assetManager = nullptr;
	if (m_fontManager)
		delete m_fontManager;
	m_fontManager = nullptr;
	if (m_renderer)
		delete m_renderer;
	m_renderer = nullptr;
	if (m_windowManager)
		delete m_windowManager;
	m_windowManager = nullptr;
}

void TextureGenEngine::Engine::Run()
{
	m_windowManager->Update();
	m_windowManager->Draw();
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
