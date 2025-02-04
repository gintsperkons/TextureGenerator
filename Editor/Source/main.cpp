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
#include <map>
#include <unordered_map>
#include <Generators/RandomNumbers.h>
#include <Core/FileHandler/FileHandler.h>

typedef std::map<
	NodeFactory::NodeType,
	std::pair<std::function<TextureGenEngine::Node *(TextureGenEngine::Canvas2D *, std::string, int, int)>, std::string>,
	NodeFactory::NodeTypeCompare>
	NodeFunctionMap;

NodeFunctionMap nodeFunctionMap = {
	{NodeFactory::NodeType::NONE, {&NodeFactory::TextNode, "None"}},
	{NodeFactory::NodeType::TEXT, {&NodeFactory::TextNode, "Text"}},
	{NodeFactory::NodeType::TEXT_MERGE, {&NodeFactory::TextMergeNode, "Text Merge"}},
	{NodeFactory::NodeType::INTEGER, {&NodeFactory::IntegerNode, "Integer"}},
	{NodeFactory::NodeType::FLOAT, {&NodeFactory::FloatNode, "Float"}},
	{NodeFactory::NodeType::NOISE_GEN_IMAGE, {&NodeFactory::NoiseGenImage, "Perlin Gen"}},
	{NodeFactory::NodeType::ADD_INT, {&NodeFactory::AddIntNode, "Add Int"}},
	{NodeFactory::NodeType::SUBTRACT_INT, {&NodeFactory::SubtractIntNode, "Subtract Int"}},
	{NodeFactory::NodeType::MULTIPLY_INT, {&NodeFactory::MultiplyIntNode, "Multiply Int"}},
	{NodeFactory::NodeType::DIVIDE_INT, {&NodeFactory::DivideIntNode, "Divide Int"}},
	{NodeFactory::NodeType::ADD_FLOAT, {&NodeFactory::AddFloatNode, "Add Float"}},
	{NodeFactory::NodeType::SUBTRACT_FLOAT, {&NodeFactory::SubtractFloatNode, "Subtract Float"}},
	{NodeFactory::NodeType::MULTIPLY_FLOAT, {&NodeFactory::MultiplyFloatNode, "Multiply Float"}},
	{NodeFactory::NodeType::DIVIDE_FLOAT, {&NodeFactory::DivideFloatNode, "Divide Float"}}};

int sideBarWidth = 300;
std::string nodeSaveFile = "nodeSaveData.tgsn";

void CreateClickables(NodeFunctionMap nodeFunctionList, TextureGenEngine::ScrollView *parentView, TextureGenEngine::Canvas2D *canvasNodeGraph)
{
	for (const auto &[nodeType, nodePair] : nodeFunctionList)
	{
		TextureGenEngine::Clickable *clickable = new TextureGenEngine::Clickable();
		clickable->OnClick([cng = canvasNodeGraph, nodeFunc = nodePair.first, title = nodePair.second]()
						   { nodeFunc(cng, title, 0, 0); });
		clickable->SetText(nodePair.second);
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

std::string CreateSaveData(std::vector<TextureGenEngine::Node *> nodes)
{
	std::string nodeSave = "";
	std::string connectionSave = "";
	for (auto &node : nodes)
	{
		TextureGenEngine::NodeInfo info;
		info = node->GetNodeInfo();
		std::string nSaveData = info.uuid + " " + std::to_string(info.nodeId) + " " + std::to_string(info.position[0]) + " " + std::to_string(info.position[1]) +  info.elementData + "\n";
		nodeSave += nSaveData;
		std::string connections = "";
		for (auto &input : info.inputConnections)
		{
			connections += input + " ";
		}
		if (connections != "")
		{
			connectionSave += info.uuid + " " + connections + "\n";
		}
	}
	return "nodes\n" + nodeSave + "connections" + ((connectionSave != "") ? "\n" + connectionSave : "");
}

void LoadSaveString(std::string saveData, TextureGenEngine::Canvas2D *canvasNodeGraph)
{
	std::unordered_map<std::string, TextureGenEngine::Node *> nodeMap;
	std::vector<std::string> lines = TextureGenEngine::SplitString(saveData, '\n');
	std::string loadingStage = "0";
	canvasNodeGraph->ClearNodes();
	for (auto &line : lines)
	{	
		if (line == "" || line == " ")
		{
			continue;
		} 
		std::vector<std::string> parts = TextureGenEngine::SplitString(line, ' ');
		if (parts[0] == "nodes")
		{
			LOG_DEBUG("Loading nodes\n");
			loadingStage = "nodes";
			continue;
		}
		if (parts[0] == "connections")
		{
			LOG_DEBUG("Loading connections\n");
			loadingStage = "connections";
			continue;
		}
		if (loadingStage == "nodes")
		{
			std::string uuid = parts[0];
			unsigned int nodeId = std::stoi(parts[1]);
			int x = std::stoi(parts[2]) - sideBarWidth;
			int y = std::stoi(parts[3]);
			nodeMap.insert({uuid, nodeFunctionMap[static_cast<NodeFactory::NodeType>(nodeId)].first(canvasNodeGraph, 
			nodeFunctionMap[static_cast<NodeFactory::NodeType>(nodeId)].second, x, y)});
			for (int i = 4; i < parts.size(); i++)
			{
				if ( parts[i] != "-=-")
				{
					nodeMap[uuid]->AddElementData(parts[i], i - 4);
				}
			}
		}
		if (loadingStage == "connections")
		{
			std::string uuid = parts[0];
			for (int i = 1; i < parts.size(); i++)
			{	
				if (parts[i] == "" || parts[i] == "0") 
				{
					continue;
				}
				std::string connectedNodeUuid = parts[i];
				nodeMap[uuid]->ConnectInput(nodeMap[connectedNodeUuid], i - 1);
			}
		}
	}
}
void handleKeyPress(KeyEvent e, TextureGenEngine::Canvas2D *canvasNodeGraph)
{
	if (TextureGenEngine::Key::KeyCode::F1 == e.key &&
		TextureGenEngine::Key::KeyAction::Press == e.action)
	{
		std::string uuid = TextureGenEngine::Random::UUID();

		LOG_DEBUG("Key pressed F1 %s\n", uuid.c_str());
	}

	if (TextureGenEngine::Key::KeyCode::S == e.key &&
		TextureGenEngine::Key::KeyAction::Press == e.action &&
		TextureGenEngine::Key::KeyModifier::Control == e.mods)
	{
		LOG_DEBUG("Key pressed ctrl + s\n");
		std::vector<TextureGenEngine::Node *> nodes(canvasNodeGraph->GetNodeCount());
		canvasNodeGraph->GetAllNodes(nodes);
		std::string saveData = CreateSaveData(nodes);
		TextureGenEngine::WriteFile(TextureGenEngine::GetAbsolutePath(nodeSaveFile), saveData);
	}
	if (TextureGenEngine::Key::KeyCode::L == e.key &&
		TextureGenEngine::Key::KeyAction::Press == e.action &&
		TextureGenEngine::Key::KeyModifier::Control == e.mods)
	{
		LOG_DEBUG("Key pressed ctrl + l\n");
		std::string saveData = TextureGenEngine::ReadFile(TextureGenEngine::GetAbsolutePath(nodeSaveFile));
		try
		{
			LoadSaveString(saveData, canvasNodeGraph);
		}
		catch (const std::exception &e)
		{
			LOG_ERROR("Error loading save data\n");
		}
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
	TextureGenEngine::Canvas2D *canvasNodeGraph = new TextureGenEngine::Canvas2D(sideBarWidth, 0, 500, 100, TextureGenEngine::ScalingType::FILL, TextureGenEngine::ScalingType::FILL);
	canvasNodeGraph->SetBackground(TextureGenEngine::Color(0.2890625f, 0.2890625f, 0.2890625f, 1.0f));
	guiManager->AddComponent(canvasNodeGraph);

	TextureGenEngine::Input::OnKeyPress([&](KeyEvent e)
										{ handleKeyPress(e, canvasNodeGraph); }, engine->GetMainWindow());

	// Create a scroll view for the clickable nodes spawners
	TextureGenEngine::ScrollView *scrollView = new TextureGenEngine::ScrollView(0, sideBarWidth, sideBarWidth, 100, TextureGenEngine::ScalingType::FIXED, TextureGenEngine::ScalingType::FILL);
	scrollView->SetBackground(TextureGenEngine::Color(0.28125f, 0.25390625f, 0.25390625f, 1.0f));
	guiManager->AddComponent(scrollView);

	CreateClickables(nodeFunctionMap, scrollView, canvasNodeGraph);

	// Create a preview panel
	TextureGenEngine::Panel *panelPreview = new TextureGenEngine::Panel(0, 0, sideBarWidth, 300, TextureGenEngine::ScalingType::FIXED, TextureGenEngine::ScalingType::FIXED);
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