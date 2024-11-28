#pragma once
#include "Defines.h"
#include <string>

struct GLFWwindow;
namespace TextureGenEngine
{
    class WindowManager;
    class GUIManager;
    class Window
    {
        WindowManager *m_manager;
        int m_id;
        std::string m_title;
        int m_width;
        int m_height;
        GLFWwindow *m_window;
        GUIManager *m_gui;

    public:
        bool ShouldClose();
        Window(WindowManager *manager, int id, const std::string &title, int width, int height);
        ~Window();
        void Update();
        void Draw();
        TAPI void AddGUI(GUIManager *gui);
    };
}
