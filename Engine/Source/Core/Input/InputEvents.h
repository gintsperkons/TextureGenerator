#pragma once
struct MouseButtonEvent
{
    MouseButtonEvent(double x, double y, int button, bool down)
        : x(x), y(y), button(button), down(down)
    {
    }

    double x;
    double y;
    int button;
    bool down;
};