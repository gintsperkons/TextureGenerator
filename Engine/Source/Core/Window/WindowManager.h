#pragma once
#include "Defines.h"
#include <vector>
#include <string>

namespace TextureGenEngine
{
    class Window;
    class WindowManager
    {
        std::vector<Window *> m_windows;
        int m_lastId = 0;
        int activeWindow = 0;

        void CloseNecessaryWindows();

    public:
        bool ShouldClose();
        WindowManager();
        ~WindowManager();
        void Update();
        Window *AddWindow(const std::string &title, int width, int height);
    };
}
