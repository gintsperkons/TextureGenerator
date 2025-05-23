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

    struct MouseMoveSub
    {
        std::function<void(MouseMoveEvent)> callback;
    };

    struct CharEventSub
    {
        std::function<void(CharEvent)> callback;
    };

    struct KeyEventSub
    {
        std::function<void(KeyEvent)> callback;
    };

    struct ScrollSub
    {
        std::function<void(ScrollEvent)> callback;
    };


    class Window;
    class Input
    {
    private:
        Window* m_window;

        std::vector<MouseClickSub> m_mouseClickSubs;
        std::vector<MouseMoveSub> m_mouseMoveSubs;
        std::vector<CharEventSub> m_charEventSubs;
        std::vector<KeyEventSub> m_keyEventSubs;
        std::vector<ScrollSub> m_scrollSubs;
        double m_xLast;
        double m_yLast;
        double m_xChange;
        double m_yChange;
    public:
        Input(Window * win);
        ~Input();
        void KeyCallback(int key, int scancode, int action, int mods);
        void CharCallback(unsigned int codepoint);
        void MouseButtonCallback(int button, int action, int mods);
        void CursorPosCallback(double xpos, double ypos);
        void ScrollCallback(double xoffset, double yoffset);
        void SubscribeToMouseClickEvents(std::function<void(MouseButtonEvent)> subscriber);
        void SubscribeToMouseMoveEvents(std::function<void(MouseMoveEvent)> subscriber);
        void SubscribeToCharEvents(std::function<void(CharEvent)> subscriber);
        void SubscribeToKeyEvents(std::function<void(KeyEvent)> subscriber);
        void SubscribeToScrollEvents(std::function<void(ScrollEvent)> subscriber);
        static TAPI void OnKeyPress(std::function<void(KeyEvent)> subscriber, Window* win);
        void GetMousePosition(double &x, double &y);
    };

    
} // namespace TextureGenEngine
