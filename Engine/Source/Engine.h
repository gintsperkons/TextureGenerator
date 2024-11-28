#pragma once
#include "Defines.h"
#include <string>

namespace TextureGenEngine
{
	class WindowManager;
	class Window;
	class Engine
	{
		
		WindowManager *m_windowManager;
		bool m_running = false;
	public:
		Engine();
		~Engine();
		TAPI void Run();
		TAPI static Engine *Get();
		TAPI bool IsRunning();
		TAPI static void Init();
		TAPI static void Shutdown();
		TAPI Window* AddWindow(const std::string &title, int width, int height);
		TAPI Window* GetMainWindow();
	};

	inline static Engine *g_engine = nullptr;
}