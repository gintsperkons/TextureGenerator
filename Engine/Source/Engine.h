#include "Defines.h"

namespace TextureGenEngine
{
	class Window;
	class Engine
	{
		Window* m_window;
	public:
		TAPI Engine();
		TAPI Engine(Window * window);
		TAPI ~Engine();
		TAPI void Run();
	};
}