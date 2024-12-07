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

#pragma once

namespace TextureGenEngine
{
    namespace Mouse
    {
        enum MouseCode
        {
            // From glfw3.h
            Button0 = 0,
            Button1 = 1,
            Button2 = 2,
            Button3 = 3,
            Button4 = 4,
            Button5 = 5,
            Button6 = 6,
            Button7 = 7,

            ButtonLast = Button7,
            ButtonLeft = Button0,
            ButtonRight = Button1,
            ButtonMiddle = Button2
        };

        enum MouseButtonState
        {
            Released = 0,
            Pressed = 1,
            Held = 2
        };

    };

}
