#pragma once
#include "Defines.h"
#include <vector>
#include <functional>

namespace TextureGenEngine
{
    class Mesh;
    class BaseElement
    {
    protected:
        std::vector<std::function<void()>> m_subscribers;
        static inline int m_menuBarHeight = 25;
        bool m_canClick = true;
        bool lockX = true;
        bool lockY = true;
        bool lockWidth = true;
        bool lockHeight = true;
        int m_x, m_y, m_width, m_height;
        std::vector<BaseElement *> m_children;
        Mesh *m_mesh = nullptr;
        BaseElement *m_parent = nullptr;
        void AddChild(BaseElement *child);

        float color[4] = {0.0f, 1.0f, 1.0f, 1.0f};

    public:
        TAPI BaseElement(int x, int y, int width, int height) : m_x(x), m_y(y), m_width(width), m_height(height) {}
        virtual void Draw() = 0;
        virtual ~BaseElement()
        {
            delete m_mesh;
            for (BaseElement *child : m_children)
            {
                delete child;
            }
        };
        virtual void Click()
        {
            for (std::function<void()> func : m_subscribers)
            {
                func();
            }
        }
        virtual void OnClick(std::function<void()> func)
        {
            m_subscribers.push_back(func);
        }
        virtual void CheckCollision(int x, int y);
        virtual void Resize(int width, int height, int oldWidth, int oldHeight);
    };
} // namespace TextureGenEngine
