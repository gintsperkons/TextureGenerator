#pragma once
#include "Defines.h"
#include "InputEvents.h"
#include <vector>
#include <functional>

namespace TextureGenEngine
{

    struct MouseClickSub
    {
        std::function<void(MouseButtonEvent)> callback;
    };

    class Window;
    class Input
    {
    private:
        Window* m_window;
        std::vector<MouseClickSub> m_mouseClickSubs;
    public:
        Input(Window * win);
        ~Input();
        void KeyCallback(int key, int scancode, int action, int mods);
        void CharCallback(unsigned int codepoint);
        void MouseButtonCallback(int button, int action, int mods);
        void CursorPosCallback(double xpos, double ypos);
        void SubscribeToMouseClickEvents(std::function<void(MouseButtonEvent)> subscriber);
    };

    
} // namespace TextureGenEngine
