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
			LOG_DEBUG("Mouse position: %d, %d\n", TextureGenEngine::Input::GetMousePosition()[0], TextureGenEngine::Input::GetMousePosition()[1]);
		}
		engine.Run();
	}
	return 0;
}