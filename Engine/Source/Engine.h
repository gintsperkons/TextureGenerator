#include "Defines.h"

namespace TextureGenEngine
{
	class Mesh;
	class Window;
	class Engine
	{
		Mesh* m_mesh;
		Window* m_window;
	public:
		TAPI Engine();
		TAPI Engine(Window * window);
		TAPI ~Engine();
		TAPI void Run();
	};
}