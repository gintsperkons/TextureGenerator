#include <Engine.h>
#include <Core/Window/Window.h>
#include <Core/GUI/GUIManager.h>
#include <Core/Input/Input.h>
#include <Core/Input/MouseCodes.h>
#include <Core/Logger/Logger.h>
#include <Core/World/Screen.h>


int main()
{

	TextureGenEngine::Engine engine(new TextureGenEngine::Window(800, 600, "TexGen"));
	//Make Gui label
	TextureGenEngine::GUIManager* guiManager = new TextureGenEngine::GUIManager;


	TextureGenEngine::Engine::Get()->GetScreen()->SetGuiMananger(guiManager);
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