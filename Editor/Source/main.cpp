#include <Engine.h>
#include <Core/Logger/Logger.h>
#include <Core/Window/Window.h>
#include <GUI/GUIManager.h>
#include <GUI/Components.h>



int main()
{
	TextureGenEngine::Engine::Init();
	TextureGenEngine::Engine *engine = TextureGenEngine::Engine::Get();


	TextureGenEngine::GUIManager *guiManager = new TextureGenEngine::GUIManager();


	TextureGenEngine::Label *label = new TextureGenEngine::Label(50,50,100,100, "Hello World");
	guiManager->AddComponent(label);

	engine->GetMainWindow()->AddGUI(guiManager);

	

	while (engine->IsRunning())
	{
		engine->Run();
	}
	TextureGenEngine::Engine::Shutdown();
	return 0;
}