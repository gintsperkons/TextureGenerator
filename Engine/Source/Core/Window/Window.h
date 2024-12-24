#pragma once
#include "Defines.h"
#include "WindowEvents.h"
#include <string>
#include <vector>
#include "Core/Input/InputEvents.h"
#include <functional>

struct GLFWwindow;
namespace TextureGenEngine
{
    struct ResizeSub {
        std::function<void(ResizeEvent)> callback;
    };


    class WindowManager;
    class GUIManager;
    class Renderer;
    class Input;
    class Window
    {
        std::vector<ResizeSub> m_resizeSubs;

        WindowManager *m_manager;
        int m_id;
        std::string m_title;
        int m_width;
        int m_height;
        GLFWwindow *m_window;
        GUIManager *m_gui;
        Input* m_input;

    public:
        bool ShouldClose();
        Window(WindowManager *manager, int id, const std::string &title, int width, int height, GLFWwindow* contextWindow = nullptr);
        ~Window();
        void Update();
        void Draw();
        void Resize(int width, int height);
        void Scissors(float x, float y, float width, float height);
        void ScissorsReset();
        TAPI void AddGUI(GUIManager *gui);
        GLFWwindow *GetWindow() { return m_window; }
        int GetWidth() { return m_width; }
        int GetHeight() { return m_height; }
        void GetFramebufferSize(int &width, int &height);
        Input* GetInput() { return m_input; }
        std::vector<ResizeSub> GetResizeSubs() { return m_resizeSubs; }
    };
}
