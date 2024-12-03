#include <Engine.h>
#include <Core/Logger/Logger.h>
#include <Core/Window/Window.h>
#include <GUI/GUIManager.h>
#include <GUI/Components.h>
#include <GUI/Color.h>
#include <GUI/ScalingType.h>



int main()
{
	TextureGenEngine::Engine::Init();
	TextureGenEngine::Engine *engine = TextureGenEngine::Engine::Get();


	TextureGenEngine::GUIManager *guiManager = new TextureGenEngine::GUIManager();


	// TextureGenEngine::Label *label = new TextureGenEngine::Label(50,50,100,100, "Hello World");
	// label->SetBackground(TextureGenEngine::Color(0.0f, 1.0f, 1.0f, 1.0f));
	// guiManager->AddComponent(label);

	TextureGenEngine::MenuBar *menuBar = new TextureGenEngine::MenuBar();
	menuBar->SetBackground(TextureGenEngine::Color(1.0f, 0.0f, 1.0f, 1.0f));
	guiManager->AddComponent(menuBar);

	TextureGenEngine::Panel *panelList = new TextureGenEngine::Panel(0, 300, 300, 100,TextureGenEngine::ScalingType::FIXED, TextureGenEngine::ScalingType::FILL);
	panelList->SetBackground(TextureGenEngine::Color(1.0f, 1.0f, 0.0f, 1.0f));
	guiManager->AddComponent(panelList);

	TextureGenEngine::Panel *panelNodeGraph = new TextureGenEngine::Panel(300, 0, 500, 100, TextureGenEngine::ScalingType::FILL, TextureGenEngine::ScalingType::FILL);
	panelNodeGraph->SetBackground(TextureGenEngine::Color(1.0f, 0.0f, 0.0f, 1.0f));
	guiManager->AddComponent(panelNodeGraph);

	TextureGenEngine::Panel *panelPreview = new TextureGenEngine::Panel(0, 0, 300, 300, TextureGenEngine::ScalingType::FIXED, TextureGenEngine::ScalingType::FIXED);
	panelPreview->SetBackground(TextureGenEngine::Color(0.0f, 0.0f, 1.0f, 1.0f));
	guiManager->AddComponent(panelPreview);

	engine->GetMainWindow()->AddGUI(guiManager);

	

	while (engine->IsRunning())
	{
		engine->Run();
	}
	TextureGenEngine::Engine::Shutdown();
	return 0;
}