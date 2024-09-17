#include "Defines.h"

namespace TextureGenEngine
{
	struct ResizeEvent;
	class Mesh;
	class Window;
	class Engine
	{
		Window* m_window;
		void ResizeCallBack(ResizeEvent event);
	public:
		TAPI Engine();
		TAPI Engine(Window * window);
		TAPI ~Engine();
		TAPI void Run();
		TAPI Window* GetWindow();
		TAPI static Engine* Get();
		TAPI bool IsRunning();
		
	};
		inline static Engine* g_engine = nullptr;
}