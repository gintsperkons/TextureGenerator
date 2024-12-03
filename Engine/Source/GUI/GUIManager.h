#pragma once
#include "Defines.h"
#include <vector>

namespace TextureGenEngine
{
    class Window;
    class Component;
    class GUIManager
    {
        std::vector<Component *> m_children;
        Window *m_window;
    public:
        TAPI GUIManager();
        ~GUIManager();
        void Update();
        void Draw();
        TAPI void AddComponent(Component *component);
        void SetWindow(Window *window) { m_window = window; }
        void Resize(int width, int height);
    };
} // namespace TextureGenEngine
