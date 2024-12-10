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

struct CharEvent
{
    CharEvent(unsigned int codepoint)
        : codepoint(codepoint)
    {
    }

    unsigned int codepoint;
};

struct KeyEvent
{
    KeyEvent(int key, int scancode, int action, int mods)
        : key(key), scancode(scancode), action(action), mods(mods)
    {
    }

    int key;
    int scancode;
    int action;
    int mods;
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

    namespace Key
    {
        enum KeyCode
        {
            // From glfw3.h
            Space = 32,
            Apostrophe = 39, /* ' */
            Comma = 44,      /* , */
            Minus = 45,      /* - */
            Period = 46,     /* . */
            Slash = 47,      /* / */
            Num0 = 48,
            Num1 = 49,
            Num2 = 50,
            Num3 = 51,
            Num4 = 52,
            Num5 = 53,
            Num6 = 54,
            Num7 = 55,
            Num8 = 56,
            Num9 = 57,
            Semicolon = 59, /* ; */
            Equal = 61,     /* = */
            A = 65,
            B = 66,
            C = 67,
            D = 68,
            E = 69,
            F = 70,
            G = 71,
            H = 72,
            I = 73,
            J = 74,
            K = 75,
            L = 76,
            M = 77,
            N = 78,
            O = 79,
            P = 80,
            Q = 81,
            R = 82,
            S = 83,
            T = 84,
            U = 85,
            V = 86,
            W = 87,
            X = 88,
            Y = 89,
            Z = 90,
            LeftBracket = 91,  /* [ */
            Backslash = 92,    /* \ */
            RightBracket = 93, /* ] */
            GraveAccent = 96,  /* ` */
            World1 = 161,      /* non-US #1 */
            World2 = 162,      /* non-US #2 */

            /* Function keys */
            Escape = 256,
            Enter = 257,
            Tab = 258,
            Backspace = 259,
            Insert = 260,
            Delete = 261,
            Right = 262,
            Left = 263,
            Down = 264,
            Up = 265,
            PageUp = 266,
            PageDown = 267,
            Home = 268,
            End = 269,
            CapsLock = 280,
            ScrollLock = 281,
            NumLock = 282,
            PrintScreen = 283,
        };
        enum Modifiers
        {
            Shift = 0x0001,
            Control = 0x0002,
            Alt = 0x0004,
            Super = 0x0008
        };
        enum KeyAction
        {
            Release = 0,
            Press = 1,
            Repeat = 2
        };
       
    } // namespace Key

}
