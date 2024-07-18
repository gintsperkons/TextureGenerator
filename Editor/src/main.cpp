#include <iostream>
#include <Core/Window/Window.h>
#include <Core/Renderer/Renderer.h>
#include <Engine.h>


int main(int argc, char const *argv[])
{

	try
	{
		TextureGen::Engine engine;
		engine.Run();
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;


}
