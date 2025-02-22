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
#include <Core/Window/Dialogs.h>
#include <GUI/Components/Canvas2D/NodeElements/NodeTypes.h>

enum class NodeCategory
{
  GEN,
  INPUT,
  PROCESS,
  OUTPUT,
  IMAGE_PROCESS
};

struct NodeCatComare
{

  bool operator()(const NodeCategory &lhs, const NodeCategory &rhs) const

  {

    return static_cast<int>(lhs) < static_cast<int>(rhs);
  }
};

typedef std::map<
    NodeFactory::NodeType,
    std::pair<std::function<TextureGenEngine::Node *(TextureGenEngine::Canvas2D *, std::string, int, int)>, std::pair<std::string, NodeCategory>>,
    NodeFactory::NodeTypeCompare>
    NodeFunctionMap;

typedef std::map<
    NodeCategory,
    std::pair<TextureGenEngine::Dropdown *, std::string>,
    NodeCatComare>
    NodeCategoryMap;

NodeCategoryMap nodeCategoryMap = {
    {NodeCategory::GEN, {nullptr, "Gen"}},
    {NodeCategory::INPUT, {nullptr, "Input"}},
    {NodeCategory::PROCESS, {nullptr, "Process"}},
    {NodeCategory::OUTPUT, {nullptr, "Output"}},
    {NodeCategory::IMAGE_PROCESS, {nullptr, "Image Process"}}
};

NodeFunctionMap nodeFunctionMap = {
    {NodeFactory::NodeType::OUTPUT, {&NodeFactory::OutputNode, {"Export Image", NodeCategory::OUTPUT}}},
    {NodeFactory::NodeType::TEXT, {&NodeFactory::TextNode, {"Text", NodeCategory::INPUT}}},
    {NodeFactory::NodeType::TEXT_MERGE, {&NodeFactory::TextMergeNode, {"Text Merge", NodeCategory::PROCESS}}},
    {NodeFactory::NodeType::INTEGER, {&NodeFactory::IntegerNode, {"Integer", NodeCategory::INPUT}}},
    {NodeFactory::NodeType::FLOAT, {&NodeFactory::FloatNode, {"Float", NodeCategory::INPUT}}},
    {NodeFactory::NodeType::PERLIN_GEN_IMAGE, {&NodeFactory::PerlinGenImage, {"Perlin Gen", NodeCategory::GEN}}},
    {NodeFactory::NodeType::ADD_INT, {&NodeFactory::AddIntNode, {"Add Int", NodeCategory::PROCESS}}},
    {NodeFactory::NodeType::SUBTRACT_INT, {&NodeFactory::SubtractIntNode, {"Subtract Int", NodeCategory::PROCESS}}},
    {NodeFactory::NodeType::MULTIPLY_INT, {&NodeFactory::MultiplyIntNode, {"Multiply Int", NodeCategory::PROCESS}}},
    {NodeFactory::NodeType::DIVIDE_INT, {&NodeFactory::DivideIntNode, {"Divide Int", NodeCategory::PROCESS}}},
    {NodeFactory::NodeType::ADD_FLOAT, {&NodeFactory::AddFloatNode, {"Add Float", NodeCategory::PROCESS}}},
    {NodeFactory::NodeType::SUBTRACT_FLOAT, {&NodeFactory::SubtractFloatNode, {"Subtract Float", NodeCategory::PROCESS}}},
    {NodeFactory::NodeType::MULTIPLY_FLOAT, {&NodeFactory::MultiplyFloatNode, {"Multiply Float", NodeCategory::PROCESS}}},
    {NodeFactory::NodeType::DIVIDE_FLOAT, {&NodeFactory::DivideFloatNode, {"Divide Float", NodeCategory::PROCESS}}},
    {NodeFactory::NodeType::CELLULAR_GEN_IMAGE, {&NodeFactory::CellularGenImage, {"Cellular Gen", NodeCategory::GEN}}},
    {NodeFactory::NodeType::MERGE_IMAGE_BY_FLOAT, {&NodeFactory::MergeImageByFloat, {"Merge Image By Float", NodeCategory::IMAGE_PROCESS}}}};

int sideBarWidth = 300;
std::string nodeSaveFile = "nodeSaveData.tgsn";

void CreateClickables(NodeFunctionMap nodeFunctionList, TextureGenEngine::ScrollView *parentView, TextureGenEngine::Canvas2D *canvasNodeGraph)
{

  for (const auto &[nodeType, nodePair] : nodeFunctionList)
  {
    if (nodeCategoryMap.find(nodePair.second.second) != nodeCategoryMap.end() && nodeCategoryMap[nodePair.second.second].first == nullptr)
    {
      nodeCategoryMap[nodePair.second.second].first = new TextureGenEngine::Dropdown();
      nodeCategoryMap[nodePair.second.second].first->SetText(nodeCategoryMap[nodePair.second.second].second);
      parentView->AddElement(nodeCategoryMap[nodePair.second.second].first);
    }
    TextureGenEngine::Dropdown *dropdown = nodeCategoryMap[nodePair.second.second].first;
    TextureGenEngine::Clickable *clickable = new TextureGenEngine::Clickable();
    clickable->SetText(nodePair.second.first);
    clickable->OnClick([cng = canvasNodeGraph, nodeFunc = nodePair.first, title = nodePair.second.first]()
                       { nodeFunc(cng, title, 0, 0); });
    dropdown->AddElement(clickable);
  }
}

void ClearNodes(TextureGenEngine::Canvas2D *canvasNodeGraph)
{
  canvasNodeGraph->ClearNodes();
}

std::string CreateSaveData(std::vector<TextureGenEngine::Node *> nodes)
{
  std::string nodeSave = "";
  std::string connectionSave = "";
  for (auto &node : nodes)
  {
    TextureGenEngine::NodeInfo info;
    info = node->GetNodeInfo();
    std::string nSaveData = info.uuid + " " + std::to_string(info.nodeId) + " " + std::to_string(info.position[0]) + " " + std::to_string(info.position[1]) + info.elementData + "\n";
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
                                                                                              nodeFunctionMap[static_cast<NodeFactory::NodeType>(nodeId)].second.first, x, y)});
      for (int i = 4; i < parts.size(); i++)
      {
        if (parts[i] != "-=-")
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

void ExportImage(TextureGenEngine::Canvas2D *canvasNodeGraph, std::string folder)
{
  LOG_DEBUG("test finut %s\n", folder);
  std::vector<TextureGenEngine::Node *> nodes(canvasNodeGraph->GetNodeCount());
  canvasNodeGraph->GetAllNodes(nodes);
  TextureGenEngine::ImagePreviewElement *imagePreview = nullptr;
  TextureGenEngine::TextualInputElement *textInput = nullptr;
  for (auto &node : nodes)
  {
    if (node->GetTypeID() == static_cast<int>(NodeFactory::NodeType::OUTPUT))
    {
      for (auto &element : node->GetElements())
      {
        if (element->GetElementType() == TextureGenEngine::ElementType::IMAGE_PREVIEW)
        {
          imagePreview = static_cast<TextureGenEngine::ImagePreviewElement *>(element);
        }
        if (element->GetElementType() == TextureGenEngine::ElementType::TEXT)
        {
          textInput = static_cast<TextureGenEngine::TextualInputElement *>(element);
        }
      }
    }
    if (imagePreview != nullptr && textInput != nullptr)
    {
      std::string fileName = "";
      textInput->GetData(fileName);
      if (fileName != "")
      {
        int width, height;
        width = imagePreview->GetImageWidth();
        height = imagePreview->GetImageHeight();
        unsigned char *data = new unsigned char[width * height * 4];
        data = imagePreview->GetCharData();
        TextureGenEngine::WriteImage(folder + "/" + fileName, "png", data, width, height, 4);
      }
    }
  }
}
void LoadNodes(TextureGenEngine::Canvas2D *canvasNodeGraph)
{
  char const *filterPatterns[1] = {"*.tgsn"};
  std::string filePath = TextureGenEngine::LoadFileDialog("Load File", "", 1, filterPatterns, "TexGen File Type", 0);
  std::string saveData = TextureGenEngine::ReadFile(filePath);
  try
  {
    LoadSaveString(saveData, canvasNodeGraph);
  }
  catch (const std::exception &e)
  {
    LOG_ERROR("Error loading save data\n");
  }
}

void SaveNodes(TextureGenEngine::Canvas2D *canvasNodeGraph)
{
  char const *filterPatterns[1] = {"*.tgsn"};
  std::string filePath = TextureGenEngine::SaveFileDialog("Select Save File", "nodeSaveData.tgsn", 1, filterPatterns, "TexGen File Type");
  LOG_DEBUG("Key pressed ctrl + s %s\n", filePath);
  std::vector<TextureGenEngine::Node *> nodes(canvasNodeGraph->GetNodeCount());
  canvasNodeGraph->GetAllNodes(nodes);
  std::string saveData = CreateSaveData(nodes);
  TextureGenEngine::WriteFile(filePath, saveData);
}

void ExportNodes(TextureGenEngine::Canvas2D *canvasNodeGraph)
{
  std::string folder = TextureGenEngine::SelectFolderDialog("Select Image Export Location", "");
  ExportImage(canvasNodeGraph, folder);
}

void SetupMenu(TextureGenEngine::MenuBar *menuBar, TextureGenEngine::Canvas2D *canvasNodeGraph)
{
  TextureGenEngine::Menu *menu = new TextureGenEngine::Menu("File");
  menu->SetBackground(TextureGenEngine::Color(0.13671875f, 0.13671875f, 0.13671875f, 1.0f));
  TextureGenEngine::MenuItem *item = new TextureGenEngine::MenuItem("Load", [canvasNodeGraph]()
                                                                    { LoadNodes(canvasNodeGraph); });
  TextureGenEngine::MenuItem *item2 = new TextureGenEngine::MenuItem("Save",  [canvasNodeGraph]() { SaveNodes(canvasNodeGraph); });
  TextureGenEngine::MenuItem *item3 = new TextureGenEngine::MenuItem("Export", [canvasNodeGraph]() { ExportNodes(canvasNodeGraph); });
  menu->AddItem(item);
  menu->AddItem(item2);
  menu->AddItem(item3);
  menuBar->AddMenu(menu);

  TextureGenEngine::Menu *menu2 = new TextureGenEngine::Menu("Options");
  menu2->SetBackground(TextureGenEngine::Color(0.13671875f, 0.13671875f, 0.13671875f, 1.0f));
  TextureGenEngine::MenuItem *item4 = new TextureGenEngine::MenuItem("Clear", [canvasNodeGraph]()
                                                                     { ClearNodes(canvasNodeGraph); });
  menu2->AddItem(item4);
  menuBar->AddMenu(menu2);
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
    char const *filterPatterns[1] = {"*.tgsn"};
    std::string filePath = TextureGenEngine::SaveFileDialog("Select Save File", "nodeSaveData.tgsn", 1, filterPatterns, "TexGen File Type");
    LOG_DEBUG("Key pressed ctrl + s %s\n", filePath);
    std::vector<TextureGenEngine::Node *> nodes(canvasNodeGraph->GetNodeCount());
    canvasNodeGraph->GetAllNodes(nodes);
    std::string saveData = CreateSaveData(nodes);
    TextureGenEngine::WriteFile(filePath, saveData);
  }
  if (TextureGenEngine::Key::KeyCode::L == e.key &&
      TextureGenEngine::Key::KeyAction::Press == e.action &&
      TextureGenEngine::Key::KeyModifier::Control == e.mods)
  {
    LOG_DEBUG("Key pressed ctrl + l\n");
    char const *filterPatterns[1] = {"*.tgsn"};
    std::string filePath = TextureGenEngine::LoadFileDialog("Load File", "", 1, filterPatterns, "TexGen File Type", 0);
    std::string saveData = TextureGenEngine::ReadFile(filePath);
    try
    {
      LoadSaveString(saveData, canvasNodeGraph);
    }
    catch (const std::exception &e)
    {
      LOG_ERROR("Error loading save data\n");
    }
  }
  if (TextureGenEngine::Key::KeyCode::E == e.key &&
      TextureGenEngine::Key::KeyAction::Press == e.action &&
      TextureGenEngine::Key::KeyModifier::Control == e.mods)
  {
    LOG_DEBUG("Key pressed ctrl + e export\n");
    std::string folder = TextureGenEngine::SelectFolderDialog("Select Image Export Location", "");
    ExportImage(canvasNodeGraph, folder);
  }
  if (TextureGenEngine::Key::KeyCode::C == e.key &&
      TextureGenEngine::Key::KeyAction::Press == e.action &&
      TextureGenEngine::Key::KeyModifier::Control == e.mods)
  {
    LOG_DEBUG("Key pressed ctrl + c clear\n");
  }
}



int main()
{
  std::vector<TextureGenEngine::Node *> nodes;
  TextureGenEngine::Engine::Init();
  TextureGenEngine::Engine *engine = TextureGenEngine::Engine::Get();

  TextureGenEngine::GUIManager *guiManager = new TextureGenEngine::GUIManager();

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

  // Create a menu bar
  TextureGenEngine::MenuBar *menuBar = new TextureGenEngine::MenuBar();
  menuBar->SetBackground(TextureGenEngine::Color(0.13671875f, 0.13671875f, 0.13671875f, 1.0f));
  guiManager->AddComponent(menuBar);
  SetupMenu(menuBar, canvasNodeGraph);

  engine->GetMainWindow()->AddGUI(guiManager);
  // Main loop
  while (engine->IsRunning())
  {
    engine->Run();
  }

  TextureGenEngine::Engine::Shutdown();

  return 0;
}
