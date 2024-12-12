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
        Node* m_parentNode = nullptr;
    public:
    
        NodeElement(/* args */);
        ~NodeElement();
        void Setup();
        void AddParentNode(Node* node) { m_parentNode = node; }
    };
} // namespace TextureGenEngine
