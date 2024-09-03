#pragma once
#include "Defines.h"
struct GLFWwindow;
namespace TextureGenEngine
{
	class Renderer;
	class Window
	{
		Renderer* m_renderer;
		GLFWwindow* m_window;
		void SwapBuffers();
		void PoolEvents();
	public:
		TAPI Window();
		TAPI Window(int width, int height, const char* title);
		~Window();
		bool ShouldClose();
		void Update();
	};
}