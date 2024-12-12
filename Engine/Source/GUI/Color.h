#pragma once
namespace TextureGenEngine
{
    typedef struct Color
    {
        float r = 1.0f;
        float g = 1.0f;
        float b = 1.0f;
        float a = 1.0f;
        Color() = default;
        explicit Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a) {}
    } Color;

} // namespace TextureGenEngine
