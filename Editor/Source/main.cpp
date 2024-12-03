#include <Engine.h>
#include <Core/Logger/Logger.h>
#include <Core/Window/Window.h>
#include <GUI/GUIManager.h>
#include <GUI/Components.h>
#include <GUI/Color.h>



int main()
{
	TextureGenEngine::Engine::Init();
	TextureGenEngine::Engine *engine = TextureGenEngine::Engine::Get();


	TextureGenEngine::GUIManager *guiManager = new TextureGenEngine::GUIManager();


	TextureGenEngine::Label *label = new TextureGenEngine::Label(50,50,100,100, "Hello World");
	label->SetBackground(TextureGenEngine::Color(0.0f, 1.0f, 1.0f, 1.0f));
	guiManager->AddComponent(label);

	engine->GetMainWindow()->AddGUI(guiManager);

	

	while (engine->IsRunning())
	{
		engine->Run();
	}
	TextureGenEngine::Engine::Shutdown();
	return 0;
}