#pragma once
#include "Defines.h"
#include "GUI/Components/Component.h"
#include <string>

namespace TextureGenEngine
{
    class Node;
    class OutputConnector;
    class InputConnector;
    class NodeElement : public Component
    {
    protected:
        std::string m_elementType;

        InputConnector *m_inputImage;
        OutputConnector *m_outputImage;

    public:
        NodeElement(/* args */);
        ~NodeElement();
        virtual void OnMouseDrag(double x, double y) override;
        virtual void Setup(int x, int y);
        virtual Component *SelectObject(double x, double y) override;
    };
} // namespace TextureGenEngine
