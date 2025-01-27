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
#include <string>
#include <functional>

void CreateClickables(std::vector<std::pair<std::function<void(TextureGenEngine::Canvas2D *, std::string)>, std::string>> nodeFunctionList, TextureGenEngine::ScrollView *parentView, TextureGenEngine::Canvas2D *canvasNodeGraph)
{
	for (const auto &[nodeFunc, title] : nodeFunctionList)
	{
		TextureGenEngine::Clickable *clickable = new TextureGenEngine::Clickable();
		clickable->OnClick([cng = canvasNodeGraph, nodeFunc, title]()
						   { nodeFunc(cng, title); });
		clickable->SetText(title);
		parentView->AddElement(clickable);
	}
}

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
		NodeFactory::TextNode(canvasNodeGraph, "Text");
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

	// Create a menu bar
	TextureGenEngine::MenuBar *menuBar = new TextureGenEngine::MenuBar();
	menuBar->SetBackground(TextureGenEngine::Color(0.13671875f, 0.13671875f, 0.13671875f, 1.0f));
	guiManager->AddComponent(menuBar);
	SetupMenu(menuBar);
	// Create a canvas for the node graph	
	TextureGenEngine::Canvas2D *canvasNodeGraph = new TextureGenEngine::Canvas2D(300, 0, 500, 100, TextureGenEngine::ScalingType::FILL, TextureGenEngine::ScalingType::FILL);
	canvasNodeGraph->SetBackground(TextureGenEngine::Color(0.2890625f, 0.2890625f, 0.2890625f, 1.0f));
	guiManager->AddComponent(canvasNodeGraph);

	TextureGenEngine::Input::OnKeyPress([&](KeyEvent e)
										{ handleKeyPress(e, canvasNodeGraph); }, engine->GetMainWindow());

	// Create a scroll view for the clickable nodes spawners
	TextureGenEngine::ScrollView *scrollView = new TextureGenEngine::ScrollView(0, 300, 300, 100, TextureGenEngine::ScalingType::FIXED, TextureGenEngine::ScalingType::FILL);
	scrollView->SetBackground(TextureGenEngine::Color(0.28125f, 0.25390625f, 0.25390625f, 1.0f));
	guiManager->AddComponent(scrollView);

	std::vector<std::pair<std::function<void(TextureGenEngine::Canvas2D *, std::string)>, std::string>> nodeFunctionList = {
		{NodeFactory::TextNode, "Text"},
		{NodeFactory::TextMergeNode, "Text Merge"},
		{NodeFactory::NoiseGenImage, "Noise Image Merge"},
	};
	CreateClickables(nodeFunctionList, scrollView, canvasNodeGraph);

	// Create a preview panel
	TextureGenEngine::Panel *panelPreview = new TextureGenEngine::Panel(0, 0, 300, 300, TextureGenEngine::ScalingType::FIXED, TextureGenEngine::ScalingType::FIXED);
	panelPreview->SetBackground(TextureGenEngine::Color(0.0f, 0.0f, 1.0f, 1.0f));
	guiManager->AddComponent(panelPreview);


	engine->GetMainWindow()->AddGUI(guiManager);
	// Main loop
	while (engine->IsRunning())
	{
		engine->Run();
	}
	TextureGenEngine::Engine::Shutdown();
	return 0;
}