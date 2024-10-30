#include "Defines.h"

namespace TextureGenEngine
{
	struct ResizeEvent;
	class Mesh;
	class Window;
	class FontManager;
	class Screen;
	class Renderer;
	class Engine
	{
		FontManager* m_fontManager;
		Window* m_window;
		Screen* m_screen;
		void ResizeCallBack(ResizeEvent event);
	public:
		TAPI Engine();
		TAPI Engine(Window * window);
		TAPI ~Engine();
		TAPI void Run();
		TAPI Window* GetWindow();
		Renderer* GetRenderer();
		TAPI TextureGenEngine::Screen* GetScreen();
		TAPI static Engine* Get();
		TAPI bool IsRunning();
		FontManager* GetFontManager(){return m_fontManager;};
		
	};
		inline static Engine* g_engine = nullptr;
}