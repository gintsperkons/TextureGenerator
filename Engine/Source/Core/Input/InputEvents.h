#pragma once
struct MouseButtonEvent
{
    MouseButtonEvent(int x, int y, int button, bool down)
        : x(x), y(y), button(button), down(down)
    {
    }

    int x;
    int y;
    int button;
    bool down;
};