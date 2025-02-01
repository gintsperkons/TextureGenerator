#pragma once
#include "Defines.h"
#include <vector>
#include "Core/Input/InputEvents.h"
struct ScissorsData
{
    
    float x, y, width, height;
    ScissorsData(float x, float y, float width, float height) : x(x), y(y), width(width), height(height) {}
};

namespace TextureGenEngine
{
    class Window;
    class Component;
    enum class Cursor;
    class GUIManager
    {   float m_oldWidth;
        float m_oldHeight;
        float m_width;
        float m_height;
        int m_cursor = 0x00036001;
        bool m_cursorChanged = false;
        std::vector<Component *> m_children;
        Window *m_window;
        int m_mouseButtonStates[Mouse::ButtonLast+1] = {0};
    std::vector<ScissorsData> m_scissors;
        Component * currentObject = nullptr;
        void SelectObject(float x, float y);

    public:
        TAPI GUIManager();
        ~GUIManager();
        void Update();
        void Draw();
        TAPI void AddComponent(Component *component);
        bool IsSelected(Component *component);
        void SetWindow(Window *window) { m_window = window; }
        void Resize(float width, float height);
        void Init(float width, float height);
        void GetOldSize(float &width, float &height);
        void MouseMove(MouseMoveEvent e);
        void MouseClick(MouseButtonEvent e);
        void CharEventAction(CharEvent e);
        void KeyAction(int key, int scancode, int action, int mods);
        void ScissorsPush(float x, float y, float width, float height);
        void ScissorsPop();
        void GetMousePosition(float &x, float &y);
        void SetCursor(Cursor cursor);
        void Scroll(float x, float y);
    };
} // namespace TextureGenEngine
