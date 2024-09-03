#pragma once
#include "Defines.h"
struct GLFWwindow;
namespace TextureGenEngine
{
	class Input;
	class Renderer;
	class Window
	{
		Renderer* m_renderer;
		GLFWwindow* m_window;
		Input* m_input;
		void SwapBuffers();
		void PoolEvents();
	public:
		TAPI Window();
		TAPI Window(int width, int height, const char* title);
		~Window();
		bool ShouldClose();
		void Update();
		GLFWwindow * GetWindow() { return m_window; }
		Renderer* GetRenderer() { return m_renderer; }
	};
}