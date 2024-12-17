#pragma once
namespace TextureGenEngine
{
    typedef struct Padding
    {
        float left = 0;
        float right = 0;
        float top = 0;
        float bottom = 0;
        Padding() = default;
        explicit Padding(float left, float right, float top, float bottom) : left(left), right(right), top(top), bottom(bottom) {}
    } Padding;

} // namespace TextureGenEngine
