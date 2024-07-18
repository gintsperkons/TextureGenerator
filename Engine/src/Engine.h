#pragma once
#include "Defines.h"
namespace TextureGen{
	class Renderer;
	class Window;
	class Engine
	{
		Window* m_window = nullptr;
		Renderer* m_renderer = nullptr;
	public:
		TAPI Engine();
		TAPI Engine(Window* starterWindow);
		TAPI void Run();
		TAPI ~Engine();
	};
}

