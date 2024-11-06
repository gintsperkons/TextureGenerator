#pragma once
#include "Defines.h"
#include <vector>

namespace TextureGenEngine
{
    class BaseElement;
    class GUIManager
    {
    private:
    int m_width, m_height;
        std::vector<BaseElement*> m_children;

    public:
        TAPI GUIManager(int width, int height);
        void Draw();
        ~GUIManager();
        void Resize(int width, int height);
        TAPI void AddChild(BaseElement* element);
    };
} // namespace TextureGenEngine
