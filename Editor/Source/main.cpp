#include <Engine.h>
#include <Core/Window/Window.h>
#include <Core/Input/Input.h>
#include <Core/Input/MouseCodes.h>
#include <Core/Logger/Logger.h>


int main()
{

	TextureGenEngine::Engine engine(new TextureGenEngine::Window(800, 600, "Texture Generator"));
	while (engine.IsRunning())
	{
		if (TextureGenEngine::Input::MouseButtonPressed(TextureGenEngine::Mouse::ButtonLeft))
		{
			LOG_DEBUG("Left mouse button pressed\n");
		}
		engine.Run();
	}
	return 0;
}