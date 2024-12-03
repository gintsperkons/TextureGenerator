#pragma once
#include "Defines.h"
#include "GUI/Color.h"

namespace TextureGenEngine
{
    class GUIManager;
    class Mesh;
    class Component
    {
        
        GUIManager *m_manager = nullptr;
        Color m_backgroundColor;

    protected:
        Mesh *m_background = nullptr;
        float m_x;
        float m_y;
        float m_width;
        float m_height;

    public:
        Component(int x, int y, int width, int height);
        virtual void Draw();
        virtual ~Component();
        virtual void Resize(int width, int height);
        TAPI virtual void SetBackground(Color color);
        void SetManager(GUIManager *manager) { m_manager = manager; }
        virtual void Init(int width, int height);
    };
} // namespace TextureGenEngine
