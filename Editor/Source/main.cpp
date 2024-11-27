#include <Engine.h>
#include <Core/Window/Window.h>
#include <Core/GUI/GUIManager.h>
#include <Core/Input/Input.h>
#include <Core/Input/MouseCodes.h>
#include <Core/Logger/Logger.h>
#include <Core/World/Screen.h>
#include <Core/GUI/Elements/Elements.h>
#include <Core/GUI/Canvas/Canvas2D.h>



void testCallback()
{
	LOG_DEBUG("Callback called Clicked Test Element\n");
}

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
	fileMenu->OnClick(testCallback);
	menuBar->AddMenu(fileMenu);
	menuBar->AddMenu(editMenu);
	menuBar->AddMenu(confMenu); 
	
	guiManager->AddChild(menuBar);



	TextureGenEngine::TextInput *textInput = new TextureGenEngine::TextInput(0, 0, 100, 25);
	guiManager->AddChild(textInput);


	

	TextureGenEngine::Canvas2D *canvas = new TextureGenEngine::Canvas2D(200, 0, bWidth - 100, bHeight - menuBar->GetMenuBarHeight());
	TextureGenEngine::Node *node = new TextureGenEngine::Node(0, 0);
	TextureGenEngine::Node *node2 = new TextureGenEngine::Node(100, 100);
	TextureGenEngine::Node *node3 = new TextureGenEngine::Node(250, 250);


	//TODO add text input to node as node element that has output

	TextureGenEngine::LineElement *line = new TextureGenEngine::LineElement(0, 0, 100, 100);

	canvas->AddElement(node);
	canvas->AddElement(node2);
	canvas->AddElement(node3);
	canvas->AddElement(line);
	guiManager->AddChild(canvas);
	



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