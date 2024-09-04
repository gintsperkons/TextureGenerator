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
	};
}