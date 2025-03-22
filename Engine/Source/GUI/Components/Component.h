#pragma once
#include "Defines.h"
#include "GUI/Color.h"
#include "GUI/Padding.h"
#include <string>

namespace TextureGenEngine
{
    class GUIManager;
    class Mesh;
    class Component
    {

    protected:
        float m_scales[2] = {1, 1};
        GUIManager *m_manager = nullptr;
        Padding m_padding;
        Color m_backgroundColor;
        Mesh *m_background = nullptr;
        Component *m_parent = nullptr;
        float m_x;
        float m_y;
        float m_width = 0;
        float m_height = 0;
        std::string m_type = "base";
        bool m_selectable = false;
        bool m_draggable = false;
        bool m_scrollable = false;

    public:
        Component(float x, float y, float width, float height);
        virtual void Draw();
        virtual ~Component();
        virtual void Resize(float width, float height);
        TAPI virtual void SetBackground(Color color);
        virtual void SetManager(GUIManager *manager) { m_manager = manager; }
        virtual void Init(float width, float height);
        void SetParent(Component *parent) { m_parent = parent; }
        float GetX() { return m_x; }
        float GetY() { return m_y; }
        float GetWidth() { return m_width; }
        float GetHeight() { return m_height; }
        virtual void Update() {}
        std::string GetType() { return m_type; }
        bool IsDraggable() { return m_draggable; }
        bool IsSelectable() { return m_selectable; }
        virtual void Select() {};
        virtual void DeSelect() {};
        virtual void Click(float x, float y) {};
        virtual bool CheckCollision(float x, float y);
        virtual Component *SelectObject(float x, float y) { return nullptr; }
        virtual void OnMouseDrag(float x, float y);
        virtual void SetDepth(float depth);
        virtual void SetPosition(float x, float y);
        virtual void Move(float x, float y);
        virtual void MouseRelease(){};
        virtual void RemoveChild(Component *child){};
        virtual void OnHover(float x, float y){};
        virtual void OnScroll(float x, float y){};

        bool IsScrollable() { return m_scrollable; }
    };
} // namespace TextureGenEngine
