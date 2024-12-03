#pragma once
#include "Defines.h"
#include <vector>

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
    public:
        TAPI GUIManager();
        ~GUIManager();
        void Update();
        void Draw();
        TAPI void AddComponent(Component *component);
        void SetWindow(Window *window) { m_window = window; }
        void Resize(int width, int height);
        void Init(int width, int height);
        void GetOldSize(float &width, float &height);
    };
} // namespace TextureGenEngine
