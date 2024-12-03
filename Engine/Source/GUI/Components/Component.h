#pragma once
#include "Defines.h"
#include "GUI/Color.h"

namespace TextureGenEngine
{
    class Mesh;
    class Component
    {
        

        Color m_backgroundColor;
        Mesh *m_background = nullptr;
    
    protected:
        int m_x;
        int m_y;
        int m_width;
        int m_height;

    public:
        Component(int x, int y, int width, int height);
        virtual void Draw();
        virtual ~Component();
    };
} // namespace TextureGenEngine
