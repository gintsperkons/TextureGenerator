#pragma once
#include "Defines.h"
struct GLFWwindow;
namespace TextureGenEngine
{
	class Window
	{
		GLFWwindow* m_window;
	public:
		TAPI Window();
		TAPI Window(int width, int height, const char* title);
		~Window();
		bool ShouldClose();
		void PoolEvents();
	};
}