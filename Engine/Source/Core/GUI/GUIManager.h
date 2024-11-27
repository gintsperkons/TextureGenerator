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
        BaseElement* m_draggableElement = nullptr;
        BaseElement* m_activeObject = nullptr;

    public:
        TAPI GUIManager(int width, int height);
        void Draw();
        ~GUIManager();
        void Click(int x, int y);
        void Drag(double x, double y);
        void InputCharacter(wchar_t character);
        void DeleteCharacter();
         void GetDraggable(int x, int y);
        void RemoveDraggable();
        void Resize(int width, int height);
        TAPI void AddChild(BaseElement* element);
    };
} // namespace TextureGenEngine
