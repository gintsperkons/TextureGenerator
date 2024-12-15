#pragma once
#include "Defines.h"
#include "GUI/Components/Component.h"
#include <string>

namespace TextureGenEngine
{
    class Node;
    class NodeElement: public Component
    {
    private:
        std::string m_elementType;
    public:

        NodeElement(/* args */);
        ~NodeElement();
        virtual void OnMouseDrag(double x, double y) override;
        virtual void Setup(int x ,int y);
        virtual Component *SelectObject(double x, double y) override { return nullptr; };
    };
} // namespace TextureGenEngine
