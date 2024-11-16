#include <Engine.h>
#include <Core/Window/Window.h>
#include <Core/GUI/GUIManager.h>
#include <Core/Input/Input.h>
#include <Core/Input/MouseCodes.h>
#include <Core/Logger/Logger.h>
#include <Core/World/Screen.h>
#include <Core/GUI/Elements/MenuBar.h>
#include <Core/GUI/Elements/Menu.h>


int main()
{


	TextureGenEngine::Engine engine(new TextureGenEngine::Window(800, 600, "TexGen"));
	int bWidth,bHeight;
	TextureGenEngine::Engine::Get()->GetWindow()->GetFramebufferSize(bWidth,bHeight);
	
	TextureGenEngine::GUIManager* guiManager = new TextureGenEngine::GUIManager(bWidth,bHeight);
	TextureGenEngine::MenuBar* menuBar = new TextureGenEngine::MenuBar();
	TextureGenEngine::Menu *fileMenu = new TextureGenEngine::Menu("File");
	TextureGenEngine::Menu *editMenu = new TextureGenEngine::Menu("Edit");
	TextureGenEngine::Menu *confMenu = new TextureGenEngine::Menu("Options");
	menuBar->AddMenu(fileMenu);
	menuBar->AddMenu(editMenu);
	menuBar->AddMenu(confMenu);
	guiManager->AddChild(menuBar);



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