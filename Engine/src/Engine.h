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
		TAPI void Run();
		TAPI ~Engine();
	};
}

