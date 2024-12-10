#include "NodeElement.h"

TextureGenEngine::NodeElement::NodeElement():
Component(0, 0, 100, 100)
{
    m_draggable = false;
    m_type = "NodeElement";
    m_elementType = "base";
}

TextureGenEngine::NodeElement::~NodeElement()
{
}

void TextureGenEngine::NodeElement::Setup()
{
}
