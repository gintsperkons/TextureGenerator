#include "Defines.h"

namespace TextureGenEngine
{
	struct ResizeEvent;
	class Mesh;
	class Window;
	class Screen;
	class Engine
	{
		Window* m_window;
		Screen* m_screen;
		void ResizeCallBack(ResizeEvent event);
	public:
		TAPI Engine();
		TAPI Engine(Window * window);
		TAPI ~Engine();
		TAPI void Run();
		TAPI Window* GetWindow();
		TAPI Screen* GetScreen();
		TAPI static Engine* Get();
		TAPI bool IsRunning();
		
	};
		inline static Engine* g_engine = nullptr;
}