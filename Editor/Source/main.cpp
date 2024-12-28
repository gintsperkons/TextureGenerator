#include <Engine.h>
#include <Core/Logger/Logger.h>
#include <Core/Window/Window.h>
#include <GUI/GUIManager.h>
#include <GUI/Components.h>
#include <GUI/Color.h>
#include <GUI/ScalingType.h>
#include <GUI/NodeElements.h>
#include <Core/Input/Input.h>
#include <Core/Input/InputEvents.h>
#include "NodeFactory.h"

void SetupMenu(TextureGenEngine::MenuBar *menuBar)
{
	TextureGenEngine::Menu *menu = new TextureGenEngine::Menu("File");
	menu->SetBackground(TextureGenEngine::Color(0.13671875f, 0.13671875f, 0.13671875f, 1.0f));
	menuBar->AddMenu(menu);

	TextureGenEngine::Menu *menu2 = new TextureGenEngine::Menu("Options");
	menu2->SetBackground(TextureGenEngine::Color(0.13671875f, 0.13671875f, 0.13671875f, 1.0f));
	menuBar->AddMenu(menu2);
}

void handleKeyPress(KeyEvent e, TextureGenEngine::Canvas2D *canvasNodeGraph)
{
	LOG_DEBUG("Key pressed %d\n", e.key);
	if (TextureGenEngine::Key::KeyCode::F1 == e.key && TextureGenEngine::Key::KeyAction::Press == e.action)
	{
		NodeFactory::TextNode(canvasNodeGraph,"Text");
	}
	if (TextureGenEngine::Key::KeyCode::F2 == e.key && TextureGenEngine::Key::KeyAction::Press == e.action)
	{
		NodeFactory::TextMergeNode(canvasNodeGraph, "Text Merge");
	}
}



int main()
{
	std::vector<TextureGenEngine::Node *> nodes;
	TextureGenEngine::Engine::Init();
	TextureGenEngine::Engine *engine = TextureGenEngine::Engine::Get();

	TextureGenEngine::GUIManager *guiManager = new TextureGenEngine::GUIManager();

	TextureGenEngine::MenuBar *menuBar = new TextureGenEngine::MenuBar();
	menuBar->SetBackground(TextureGenEngine::Color(0.13671875f, 0.13671875f, 0.13671875f, 1.0f));
	guiManager->AddComponent(menuBar);
	SetupMenu(menuBar);

	TextureGenEngine::Panel *scrollView = new TextureGenEngine::Panel(0, 300, 300, 100, TextureGenEngine::ScalingType::FIXED, TextureGenEngine::ScalingType::FILL);
	scrollView->SetBackground(TextureGenEngine::Color(0.28125f, 0.25390625f, 0.25390625f, 1.0f));
	guiManager->AddComponent(scrollView);

	TextureGenEngine::Panel *panelPreview = new TextureGenEngine::Panel(0, 0, 300, 300, TextureGenEngine::ScalingType::FIXED, TextureGenEngine::ScalingType::FIXED);
	panelPreview->SetBackground(TextureGenEngine::Color(0.0f, 0.0f, 1.0f, 1.0f));
	guiManager->AddComponent(panelPreview);

	TextureGenEngine::Canvas2D *canvasNodeGraph = new TextureGenEngine::Canvas2D(300, 0, 500, 100, TextureGenEngine::ScalingType::FILL, TextureGenEngine::ScalingType::FILL);
	canvasNodeGraph->SetBackground(TextureGenEngine::Color(0.2890625f, 0.2890625f, 0.2890625f, 1.0f));
	guiManager->AddComponent(canvasNodeGraph);

	TextureGenEngine::Input::OnKeyPress([&](KeyEvent e) {
		handleKeyPress(e, canvasNodeGraph);
	}, engine->GetMainWindow());

	engine->GetMainWindow()->AddGUI(guiManager);

	while (engine->IsRunning())
	{
		engine->Run();
	}
	TextureGenEngine::Engine::Shutdown();
	return 0;
}