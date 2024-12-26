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

int main()
{
	std::vector<TextureGenEngine::Node *> nodes;
	TextureGenEngine::Engine::Init();
	TextureGenEngine::Engine *engine = TextureGenEngine::Engine::Get();

	TextureGenEngine::GUIManager *guiManager = new TextureGenEngine::GUIManager();

	TextureGenEngine::MenuBar *menuBar = new TextureGenEngine::MenuBar();
	menuBar->SetBackground(TextureGenEngine::Color(0.13671875f, 0.13671875f, 0.13671875f, 1.0f));
	guiManager->AddComponent(menuBar);

	TextureGenEngine::Menu *menu = new TextureGenEngine::Menu("File");
	menu->SetBackground(TextureGenEngine::Color(0.13671875f, 0.13671875f, 0.13671875f, 1.0f));
	menuBar->AddMenu(menu);

	TextureGenEngine::Menu *menu2 = new TextureGenEngine::Menu("Options");
	menu2->SetBackground(TextureGenEngine::Color(0.13671875f, 0.13671875f, 0.13671875f, 1.0f));
	menuBar->AddMenu(menu2);

	TextureGenEngine::Panel *scrollView = new TextureGenEngine::Panel(0, 300, 300, 100, TextureGenEngine::ScalingType::FIXED, TextureGenEngine::ScalingType::FILL);
	scrollView->SetBackground(TextureGenEngine::Color(0.28125f, 0.25390625f, 0.25390625f, 1.0f));
	guiManager->AddComponent(scrollView);

	TextureGenEngine::Label *label = new TextureGenEngine::Label(0, 0, 100, 100, "");

	TextureGenEngine::Panel *panelPreview = new TextureGenEngine::Panel(0, 0, 300, 300, TextureGenEngine::ScalingType::FIXED, TextureGenEngine::ScalingType::FIXED);
	panelPreview->SetBackground(TextureGenEngine::Color(0.0f, 0.0f, 1.0f, 1.0f));
	guiManager->AddComponent(panelPreview);

	TextureGenEngine::Canvas2D *canvasNodeGraph = new TextureGenEngine::Canvas2D(300, 0, 500, 100, TextureGenEngine::ScalingType::FILL, TextureGenEngine::ScalingType::FILL);
	canvasNodeGraph->SetBackground(TextureGenEngine::Color(0.2890625f, 0.2890625f, 0.2890625f, 1.0f));
	guiManager->AddComponent(canvasNodeGraph);

	TextureGenEngine::Input::OnKeyPress([&](KeyEvent e)
										{
		if (TextureGenEngine::Key::KeyCode::F1 == e.key && TextureGenEngine::Key::KeyAction::Press == e.action){
		TextureGenEngine::Node *temp = new TextureGenEngine::Node(100, 200);
		temp->SetBackground(TextureGenEngine::Color(0.0f, 0.0f, 0.0f, 1.0f));
		TextureGenEngine::IntegerElement *intElement = new TextureGenEngine::IntegerElement();
		intElement->SetBackground(TextureGenEngine::Color(0.0f, 0.0f, 0.0f, 0.0f));
		canvasNodeGraph->AddNode(temp);
		temp->AddElement(intElement);
		} }, engine->GetMainWindow());

	engine->GetMainWindow()->AddGUI(guiManager);

	while (engine->IsRunning())
	{
		engine->Run();
	}
	TextureGenEngine::Engine::Shutdown();
	return 0;
}