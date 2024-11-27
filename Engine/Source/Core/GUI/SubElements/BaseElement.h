#pragma once
#include "Defines.h"
#include <vector>
#include <functional>
#include <string>

namespace TextureGenEngine
{
    class Mesh;
    class BaseElement
    {
    protected:
        std::vector<std::function<void()>> m_subscribers;
        static inline int m_menuBarHeight = 25;
        bool m_selectable = false;
        bool m_alignTop = false;
        bool m_alignLeft = false;
        bool m_canClick = true;
        bool m_draggable = false;
        bool m_scaleHeight = false;
        bool m_scaleWidth = false;
        bool m_resizeUpdateX = true;
        bool m_resizeUpdateY = true;
        bool m_writable = false;
        std::string m_inputText = "";

        float m_x, m_y, m_width, m_height;
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
        virtual void GetDimensions(int &width, int &height)
        {
            width = m_width;
            height = m_height;
        }
        virtual void GetPosition(float &x, float &y)
        {
            x = m_x;
            y = m_y;
        }
        virtual BaseElement *GetDraggable(int x, int y);
        virtual void OnClick(std::function<void()> func)
        {
            m_subscribers.push_back(func);
        }
        virtual void Drag(double x, double y);
        virtual void InputCharacter(wchar_t character);
        virtual void DeleteCharacter();
        virtual BaseElement *CheckCollision(int x, int y);
        virtual void Resize(int width, int height, int oldWidth, int oldHeight);
        virtual void UpdatePositionByMouseDelta(double x, double y);
        virtual void UpdatePositionRelativeToParent(int x, int y);
    };
} // namespace TextureGenEngine
