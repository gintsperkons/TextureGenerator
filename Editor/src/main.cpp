#include <iostream>
#include <Core/Window/Window.h>

int main(int argc, char const *argv[])
{
    TextureGen::Window window(800, 600, "My Lovely Window");
    while (!window.ShouldClose())
    {
        window.PollEvents();
    }
    return 0;
}
