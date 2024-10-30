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
	int bWidth,bHeight;
	TextureGenEngine::Engine::Get()->GetWindow()->GetFramebufferSize(bWidth,bHeight);
	
	TextureGenEngine::GUIManager* guiManager = new TextureGenEngine::GUIManager(bWidth,bHeight);
	


	TextureGenEngine::Engine::Get()->GetScreen()->SetGUIManager(guiManager);
	
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