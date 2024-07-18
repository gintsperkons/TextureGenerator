#include <iostream>
#include <Core/Window/Window.h>
#include <Core/Renderer/Renderer.h>

int main(int argc, char const *argv[])
{
	try
	{
		TextureGen::Window window(800, 600, "My Lovely Window");
		TextureGen::Renderer renderer;
		renderer.InitRenderer(TextureGen::RendererType::Vulkan, window.GetWindow());
		
		while (!window.ShouldClose())
		{
			window.PollEvents();
		}
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
    return EXIT_SUCCESS;
}
