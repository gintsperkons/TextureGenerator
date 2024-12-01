#pragma once
#include "Defines.h"
#include <vector>

namespace TextureGenEngine
{
    class Component;
    class GUIManager
    {
        std::vector<Component *> m_children;

    public:
        TAPI GUIManager();
        ~GUIManager();
        void Update();
        void Draw();
        TAPI void AddComponent(Component *component);
    };
} // namespace TextureGenEngine
