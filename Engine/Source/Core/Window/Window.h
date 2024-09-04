#pragma once
#include "Defines.h"
#include "WindowEvents.h"
#include <vector>
#include <functional>
struct GLFWwindow;
namespace TextureGenEngine
{
	class Input;
	class Renderer;
	class Mesh;

	class Window
	{
		struct ResizeSub {
			std::function<void(ResizeEvent)> callback;
		};
		std::vector<ResizeSub> m_resizeSubs;
		Renderer* m_renderer;
		GLFWwindow* m_window;
		Mesh* m_mesh;
		Input* m_input;
		void SwapBuffers();
		void PoolEvents();
	public:
		TAPI Window();
		TAPI Window(int width, int height, const char* title);
		~Window();
		bool ShouldClose();
		void Update();
		void Draw();
		GLFWwindow * GetWindow() { return m_window; }
		Renderer* GetRenderer() { return m_renderer; }

		void OnResize();

		void AddResizeListener(std::function<void(ResizeEvent)> callback);
	};
}