#pragma once
#include "Defines.h"
#include <vector>
#include "Core/Input/InputEvents.h"

namespace TextureGenEngine
{
    class Window;
    class Component;
    class GUIManager
    {   float m_oldWidth;
        float m_oldHeight;
        float m_width;
        float m_height;
        std::vector<Component *> m_children;
        Window *m_window;
        int m_mouseButtonStates[Mouse::ButtonLast+1] = {0};

        Component * currentObject = nullptr;
        void SelectObject(double x, double y);

    public:
        TAPI GUIManager();
        ~GUIManager();
        void Update();
        void Draw();
        TAPI void AddComponent(Component *component);
        bool IsSelected(Component *component);
        void SetWindow(Window *window) { m_window = window; }
        void Resize(int width, int height);
        void Init(int width, int height);
        void GetOldSize(float &width, float &height);
        void Scissors(int x, int y, int width, int height);
        void MouseMove(MouseMoveEvent e);
        void MouseClick(MouseButtonEvent e);
        void CharEventAction(CharEvent e);
        void KeyAction(int key, int scancode, int action, int mods);
        
        void ScissorsReset();
    };
} // namespace TextureGenEngine