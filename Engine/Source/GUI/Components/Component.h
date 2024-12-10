#pragma once
#include "Defines.h"
#include "GUI/Color.h"
#include <string>

namespace TextureGenEngine
{
    class GUIManager;
    class Mesh;
    class Component
    {
        

    protected:
        GUIManager *m_manager = nullptr;
        Color m_backgroundColor;
        Mesh *m_background = nullptr;
        Component *m_parent = nullptr;
        float m_x;
        float m_y;
        float m_width;
        float m_height;
        std::string m_type = "base";
        bool m_selectable = false;
        bool m_draggable = false;

    public:
        Component(int x, int y, int width, int height);
        virtual void Draw();
        virtual ~Component();
        virtual void Resize(int width, int height);
        TAPI virtual void SetBackground(Color color);
        void SetManager(GUIManager *manager) { m_manager = manager; }
        virtual void Init(int width, int height);
        void SetParent(Component *parent) { m_parent = parent; }
        float GetX() { return m_x; }
        float GetY() { return m_y; }
        float GetWidth() { return m_width; }
        float GetHeight() { return m_height; }
        std::string GetType() { return m_type; }
        bool IsDraggable() { return m_draggable; }
        bool IsSelectable() { return m_selectable; }
        virtual void Click(float x, float y) {};
        virtual bool CheckCollision(float x, float y);
        virtual Component *SelectObject(double x, double y) { return nullptr; }
        virtual void OnMouseDrag(double x, double y);

    };
} // namespace TextureGenEngine
