#include "Label.h"

TextureGenEngine::Label::Label(int x, int y, int width, int height, const std::string &text)
: Component(x,y,width,height)
{
}

TextureGenEngine::Label::~Label()
{
}

void TextureGenEngine::Label::Draw()
{
    Component::Draw();
}
