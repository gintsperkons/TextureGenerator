#pragma once
#include "Defines.h"
#include "InputEvents.h"

namespace TextureGenEngine
{
    class Window;
    class Input
    {
    private:
        Window* m_window;
    public:
        Input(Window * win);
        ~Input();
        void KeyCallback(int key, int scancode, int action, int mods);
        void CharCallback(unsigned int codepoint);
        void MouseButtonCallback(int button, int action, int mods);
        void CursorPosCallback(double xpos, double ypos);
    };

    
} // namespace TextureGenEngine
