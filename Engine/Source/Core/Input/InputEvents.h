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
struct MouseMoveEvent
{
    MouseMoveEvent(double x, double y)
        : x(x), y(y)
    {
    }

    double x;
    double y;
};