#include <Engine.h>
#include <Core/Window/Window.h>

int main()
{

	TextureGenEngine::Engine engine(new TextureGenEngine::Window(800,600,"Texture Generator"));
	engine.Run();
	return 0;
}