#pragma once
#include "Defines.h"
#include <string>

struct GLFWwindow;
namespace TextureGenEngine
{
    class WindowManager;
    class Window
    {
        WindowManager *m_manager;
        int m_id;
        std::string m_title;
        int m_width;
        int m_height;
        GLFWwindow *m_window;

    public:
        bool ShouldClose();
        Window(WindowManager *manager, int id, const std::string &title, int width, int height);
        ~Window();
        void Update();
    };
}
