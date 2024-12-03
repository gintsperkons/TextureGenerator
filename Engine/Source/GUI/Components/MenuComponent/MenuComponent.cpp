#include "MenuComponent.h"

TextureGenEngine::MenuComponent::MenuComponent(int height):
Component(0,0,100,height)
{
}

void TextureGenEngine::MenuComponent::Draw()
{
    Component::Draw();
}

TextureGenEngine::MenuComponent::~MenuComponent()
{
}
