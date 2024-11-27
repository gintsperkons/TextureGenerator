#pragma once
#include "Defines.h"
#include "WindowEvents.h"
#include <vector>
#include <functional>
#include "Core/Asserts.h"
struct GLFWwindow;
namespace TextureGenEngine
{
	class Renderer;
	class Mesh;

	class Window
	{
		int m_width;
		int m_height;

		struct ResizeSub
		{
			std::function<void(ResizeEvent)> callback;
		};
		struct CharacterSub
		{
			std::function<void(CharacterEvent)> callback;
		};
		std::vector<ResizeSub> m_resizeSubs;
		std::vector<CharacterSub> m_characterSubs;
		Renderer *m_renderer;
		GLFWwindow *m_window;
		Mesh *m_mesh;
		void SwapBuffers();
		void PoolEvents();
		void UpdateKeyStates();
		void UpdateMouseButtons();

	public:
		TAPI Window();
		TAPI Window(int width, int height, const char *title);
		~Window();
		bool ShouldClose();
		bool IsMinimized();
		void Update();
		void Draw();
		GLFWwindow *GetNativeWindow()
		{
			return m_window;
		}
		Renderer *GetRenderer()
		{
			return m_renderer;
		}
		void OnResize();
		void OnCharacter(int codepoint);
		TAPI void GetFramebufferSize(int &width, int &height);
		int GetWidth() { return m_width; }
		int GetHeight() { return m_height; }
		void AddResizeListener(std::function<void(ResizeEvent)> callback);
		void AddCharacterListener(std::function<void(CharacterEvent)> callback);
	};
}