#pragma once
#include "Defines.h"

namespace TextureGenEngine
{
    class Mesh;
    class Component
    {
        float m_backgroundColor[4];
        Mesh *m_background = nullptr;

    public:
        Component(int x, int y, int width, int height);
        virtual void Draw();
        virtual ~Component();
    };
} // namespace TextureGenEngine
