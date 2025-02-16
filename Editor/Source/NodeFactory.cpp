#include "NodeFactory.h"
#include "GUI/Components/Canvas2D/NodeElements/OutputConnector.h"
#include "GUI/Components/Canvas2D/NodeElements/NodeTypes.h"
#include "Generators/Generators.h"
#include "Generators/RandomNumbers.h"
#include "Core/Logger/Logger.h"
#include "GUI/Components/Canvas2D/NodeElements/NodeTypes.h"
#include "ImageJobQueue.h"
#include <future>
#include <type_traits>
#include <mutex>

static const int c_imageSize = 2048;
static ImageJobQueue imageWorkerQueue = ImageJobQueue();

static void GenerateImage(float *imagePtr, std::vector<TextureGenEngine::PatternGeneratorData> operationList, int width, int height)
{
  LOG_DEBUG("Generating image\n");
  LOG_DEBUG("Width %d Height %d\n", width, height);
  if (operationList.size() == 0 || imagePtr == nullptr || width == 0 || height == 0)
  {
    return;
  }

  TextureGenEngine::PatternGeneratorData data;
  for (int i = 0; i < operationList.size(); i++)
  {
    data = operationList[i];
    data.generator(imagePtr, width, height, data.frequency, data.seed);
  }
}

static TextureGenEngine::Node *SpawnNode(TextureGenEngine::Canvas2D *canvas, std::string title, NodeFactory::NodeType nodeId = NodeFactory::NodeType::NONE, int x = 0, int y = 0)
{
  float spawnX, spawnY;
  spawnX = x;
  spawnY = y;
  if (nodeId == NodeFactory::NodeType::NONE)
  {
    LOG_ERROR("Node type not set\n");
    return nullptr;
  }
  if (x == 0 && y == 0)
    canvas->GetSpawnLocation(spawnX, spawnY);
  TextureGenEngine::Node *node = new TextureGenEngine::Node(spawnX, spawnY, int(nodeId));
  canvas->AddNode(node);
  node->SetBackground(TextureGenEngine::Color(0.0f, 0.0f, 0.0f, 1.0f));
  node->SetTitle(title);
  return node;
};

static TextureGenEngine::OutputConnector *SetOutputConnector(TextureGenEngine::Node *node, TextureGenEngine::NodeDataTypes type)
{
  TextureGenEngine::OutputConnector *outElement = new TextureGenEngine::OutputConnector();
  outElement->SetDataType(type);
  node->SetOutput(outElement);
  return outElement;
}

template <typename T, typename std::enable_if<std::is_base_of<TextureGenEngine::NodeElement, T>::value, int>::type = 0>
static T *AddNodeElement(TextureGenEngine::Node *node, TextureGenEngine::Color color = TextureGenEngine::Color(0.0f, 0.0f, 0.0f, 0.0f))
{
  T *el = new T();
  el->SetBackground(color);
  node->AddElement(el);
  return el;
}

TextureGenEngine::Node *NodeFactory::OutputNode(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::OUTPUT, x, y);

  TextureGenEngine::TextualInputElement *textInput = AddNodeElement<TextureGenEngine::TextualInputElement>(node);

  TextureGenEngine::ImageInputElement *imageInput = AddNodeElement<TextureGenEngine::ImageInputElement>(node);

  TextureGenEngine::ImagePreviewElement *imagePreview = AddNodeElement<TextureGenEngine::ImagePreviewElement>(node);

  std::function updateImage = [imagePreview, imageInput]()
  {
    TextureGenEngine::TextureData *td = imageInput->GetData();
    if (td == nullptr)
      return;
    imagePreview->LoadingScreen();
    imagePreview->SetImageSize(c_imageSize, c_imageSize);

    imagePreview->SetTextureData(td);

    // imageWorkerQueue.AddJob([imagePointer, operationList, width, imagePreview]()
    //                         {
    //                                 std::mutex imageMutex;
    //                                 {
    //                                     std::lock_guard<std::mutex> lock(imageMutex);
    //                                     GenerateImage(imagePointer, operationList, width, width);
    //                                 }
    //                             imagePreview->UpdateImage(); });
  };

  imageInput->SetOnDataChange(updateImage);

  return node;
}

TextureGenEngine::Node *NodeFactory::TextNode(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::TEXT, x, y);

  TextureGenEngine::TextualInputElement *textInput = AddNodeElement<TextureGenEngine::TextualInputElement>(node);

  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::TEXT);

  textInput->SetOnDataChange([outElement]()
                             { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([textInput, outElement]()
                          {
        std::string text = "";
        textInput->GetData(text);
        outElement->UpdateData(text); });

  return node;
}

TextureGenEngine::Node *NodeFactory::TextMergeNode(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::TEXT_MERGE, x, y);

  TextureGenEngine::TextualInputElement *textFirst = AddNodeElement<TextureGenEngine::TextualInputElement>(node);
  TextureGenEngine::TextualInputElement *textSecond = AddNodeElement<TextureGenEngine::TextualInputElement>(node);

  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::TEXT);

  textFirst->SetOnDataChange([outElement]()
                             { outElement->TriggerUpdate(); });

  textSecond->SetOnDataChange([outElement]()
                              { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([textFirst, textSecond, outElement]()
                          {
                                std::string text1 = "";
                                std::string text2 = "";
                                textFirst->GetData(text1);
                                textSecond->GetData(text2);
                                outElement->UpdateData(text1 + text2); });

  return node;
}

TextureGenEngine::Node *NodeFactory::IntegerNode(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::INTEGER, x, y);
  TextureGenEngine::IntegerElement *intInput = AddNodeElement<TextureGenEngine::IntegerElement>(node);
  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::INTEGER);

  intInput->SetOnDataChange([outElement]()
                            { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([intInput, outElement]()
                          {
                                int value;
                                intInput->GetData(value);
                                outElement->UpdateData(value); });

  return node;
}

TextureGenEngine::Node *NodeFactory::FloatNode(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::FLOAT, x, y);
  TextureGenEngine::FloatInputElement *floatInput = AddNodeElement<TextureGenEngine::FloatInputElement>(node);
  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::FLOAT);

  floatInput->SetOnDataChange([outElement]()
                              { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([floatInput, outElement]()
                          {
                                float value;
                                floatInput->GetData(value);
                                outElement->UpdateData(value); });

  return node;
}

TextureGenEngine::Node *NodeFactory::AddIntNode(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::ADD_INT, x, y);
  TextureGenEngine::IntegerElement *intInput1 = AddNodeElement<TextureGenEngine::IntegerElement>(node);
  TextureGenEngine::IntegerElement *intInput2 = AddNodeElement<TextureGenEngine::IntegerElement>(node);
  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::INTEGER);

  intInput1->SetOnDataChange([outElement]()
                             { outElement->TriggerUpdate(); });

  intInput2->SetOnDataChange([outElement]()
                             { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([intInput1, intInput2, outElement]()
                          {
                                int value1;
                                int value2;
                                intInput1->GetData(value1);
                                intInput2->GetData(value2);
                                outElement->UpdateData(value1 + value2); });

  return node;
}

TextureGenEngine::Node *NodeFactory::SubtractIntNode(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::ADD_FLOAT, x, y);
  TextureGenEngine::IntegerElement *intInput1 = AddNodeElement<TextureGenEngine::IntegerElement>(node);
  TextureGenEngine::IntegerElement *intInput2 = AddNodeElement<TextureGenEngine::IntegerElement>(node);
  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::INTEGER);

  intInput1->SetOnDataChange([outElement]()
                             { outElement->TriggerUpdate(); });

  intInput2->SetOnDataChange([outElement]()
                             { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([intInput1, intInput2, outElement]()
                          {
                                int value1;
                                int value2;
                                intInput1->GetData(value1);
                                intInput2->GetData(value2);
                                outElement->UpdateData(value1 - value2); });

  return node;
}

TextureGenEngine::Node *NodeFactory::MultiplyIntNode(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::MULTIPLY_INT, x, y);
  TextureGenEngine::IntegerElement *intInput1 = AddNodeElement<TextureGenEngine::IntegerElement>(node);
  TextureGenEngine::IntegerElement *intInput2 = AddNodeElement<TextureGenEngine::IntegerElement>(node);
  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::INTEGER);

  intInput1->SetOnDataChange([outElement]()
                             { outElement->TriggerUpdate(); });

  intInput2->SetOnDataChange([outElement]()
                             { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([intInput1, intInput2, outElement]()
                          {
                                int value1;
                                int value2;
                                intInput1->GetData(value1);
                                intInput2->GetData(value2);
                                outElement->UpdateData(value1 * value2); });

  return node;
}

TextureGenEngine::Node *NodeFactory::DivideIntNode(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::DIVIDE_INT, x, y);
  TextureGenEngine::IntegerElement *intInput1 = AddNodeElement<TextureGenEngine::IntegerElement>(node);
  TextureGenEngine::IntegerElement *intInput2 = AddNodeElement<TextureGenEngine::IntegerElement>(node);
  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::INTEGER);

  intInput1->SetOnDataChange([outElement]()
                             { outElement->TriggerUpdate(); });

  intInput2->SetOnDataChange([outElement]()
                             { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([intInput1, intInput2, outElement]()
                          {
                                int value1;
                                int value2;
                                intInput1->GetData(value1);
                                intInput2->GetData(value2);
                                if (value2 == 0)
                                    outElement->UpdateData(0);
                                else
                                    outElement->UpdateData(value1 / value2); });

  return node;
}

TextureGenEngine::Node *NodeFactory::AddFloatNode(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::ADD_FLOAT, x, y);
  TextureGenEngine::FloatInputElement *floatInput1 = AddNodeElement<TextureGenEngine::FloatInputElement>(node);
  TextureGenEngine::FloatInputElement *floatInput2 = AddNodeElement<TextureGenEngine::FloatInputElement>(node);
  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::FLOAT);

  floatInput1->SetOnDataChange([outElement]()
                               { outElement->TriggerUpdate(); });

  floatInput2->SetOnDataChange([outElement]()
                               { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([floatInput1, floatInput2, outElement]()
                          {
                                float value1;
                                float value2;
                                floatInput1->GetData(value1);
                                floatInput2->GetData(value2);
                                outElement->UpdateData(value1 + value2); });

  return node;
}

TextureGenEngine::Node *NodeFactory::SubtractFloatNode(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::SUBTRACT_FLOAT, x, y);
  TextureGenEngine::FloatInputElement *floatInput1 = AddNodeElement<TextureGenEngine::FloatInputElement>(node);
  TextureGenEngine::FloatInputElement *floatInput2 = AddNodeElement<TextureGenEngine::FloatInputElement>(node);
  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::FLOAT);

  floatInput1->SetOnDataChange([outElement]()
                               { outElement->TriggerUpdate(); });

  floatInput2->SetOnDataChange([outElement]()
                               { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([floatInput1, floatInput2, outElement]()
                          {
                                float value1;
                                float value2;
                                floatInput1->GetData(value1);
                                floatInput2->GetData(value2);
                                outElement->UpdateData(value1 - value2); });

  return node;
}

TextureGenEngine::Node *NodeFactory::MultiplyFloatNode(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::MULTIPLY_FLOAT, x, y);
  TextureGenEngine::FloatInputElement *floatInput1 = AddNodeElement<TextureGenEngine::FloatInputElement>(node);
  TextureGenEngine::FloatInputElement *floatInput2 = AddNodeElement<TextureGenEngine::FloatInputElement>(node);
  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::FLOAT);

  floatInput1->SetOnDataChange([outElement]()
                               { outElement->TriggerUpdate(); });

  floatInput2->SetOnDataChange([outElement]()
                               { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([floatInput1, floatInput2, outElement]()
                          {
                                float value1;
                                float value2;
                                floatInput1->GetData(value1);
                                floatInput2->GetData(value2);
                                outElement->UpdateData(value1 * value2); });

  return node;
}

TextureGenEngine::Node *NodeFactory::DivideFloatNode(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::DIVIDE_FLOAT, x, y);
  TextureGenEngine::FloatInputElement *floatInput1 = AddNodeElement<TextureGenEngine::FloatInputElement>(node);
  TextureGenEngine::FloatInputElement *floatInput2 = AddNodeElement<TextureGenEngine::FloatInputElement>(node);
  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::FLOAT);

  floatInput1->SetOnDataChange([outElement]()
                               { outElement->TriggerUpdate(); });

  floatInput2->SetOnDataChange([outElement]()
                               { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([floatInput1, floatInput2, outElement]()
                          {
                                float value1;
                                float value2;
                                floatInput1->GetData(value1);
                                floatInput2->GetData(value2);
                                if (value2 == 0)
                                    outElement->UpdateData(0);
                                else
                                    outElement->UpdateData(value1 / value2); });

  return node;
}

TextureGenEngine::Node *NodeFactory::PerlinGenImage(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::PERLIN_GEN_IMAGE, x, y);
  TextureGenEngine::FloatInputElement *frequencyInput = AddNodeElement<TextureGenEngine::FloatInputElement>(node);
  TextureGenEngine::IntegerElement *seedInput = AddNodeElement<TextureGenEngine::IntegerElement>(node);
  TextureGenEngine::ImagePreviewElement *imagePreview = AddNodeElement<TextureGenEngine::ImagePreviewElement>(node);
  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::PATTERNGENERATOR);

  frequencyInput->SetData(0.1f);
  seedInput->SetData(TextureGenEngine::Random::RandInt(0, 1000000));

  imagePreview->SetImageSize(c_imageSize, c_imageSize);
  


  std::function generateImage = [frequencyInput, seedInput, imagePreview, node, outElement]()
  {
    int seed;
    float frequency;
    frequencyInput->GetData(frequency);
    imagePreview->LoadingScreen();
    seedInput->GetData(seed);
    imageWorkerQueue.AddJob(node->GetUUID(), [outElement, imagePreview, frequency, seed](std::shared_ptr<std::atomic<bool>> cancelFlag)
                            { if (cancelFlag.get()->load())
                               return;
                                    TextureGenEngine::PatternGenerator::Perlin::GenTileable2D(imagePreview->GetImageDataPtr(), imagePreview->GetImageWidth(), imagePreview->GetImageHeight(), frequency, seed);
                                    if (cancelFlag.get()->load()) 
                                      return;
                                                  imagePreview->UpdateImage(); });
  };

  frequencyInput->SetOnDataChange([generateImage]()
                                  { generateImage(); });

  seedInput->SetOnDataChange([generateImage]()
                             { generateImage(); });

  imagePreview->SetOnImageChange([outElement]()
                                 { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([imagePreview, outElement]()
                          { outElement->UpdateData(imagePreview->GetImageData()); });

  generateImage();
  return node;
}

TextureGenEngine::Node *NodeFactory::CellularGenImage(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::CELLULAR_GEN_IMAGE, x, y);
  TextureGenEngine::FloatInputElement *frequencyInput = AddNodeElement<TextureGenEngine::FloatInputElement>(node);
  TextureGenEngine::IntegerElement *seedInput = AddNodeElement<TextureGenEngine::IntegerElement>(node);
  TextureGenEngine::ImagePreviewElement *imagePreview = AddNodeElement<TextureGenEngine::ImagePreviewElement>(node);
  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::PATTERNGENERATOR);

  frequencyInput->SetData(0.1f);
  seedInput->SetData(TextureGenEngine::Random::RandInt(0, 1000000));

  imagePreview->SetImageSize(c_imageSize, c_imageSize);

  std::function generateImage = [frequencyInput, seedInput, imagePreview, node, outElement]()
  {
    int seed;
    float frequency;
    frequencyInput->GetData(frequency);
    imagePreview->LoadingScreen();
    seedInput->GetData(seed);
    imageWorkerQueue.AddJob(node->GetUUID(), [outElement, imagePreview, frequency, seed](std::shared_ptr<std::atomic<bool>> cancelFlag)
                            { if (cancelFlag.get()->load())
                               return;
                                    TextureGenEngine::PatternGenerator::Cellular::GenTileable2D(imagePreview->GetImageDataPtr(), imagePreview->GetImageWidth(), imagePreview->GetImageHeight(), frequency, seed);
                                    if (cancelFlag.get()->load()) 
                                      return;
                                                  imagePreview->UpdateImage(); });
  };

  frequencyInput->SetOnDataChange([generateImage]()
                                  { generateImage(); });

  seedInput->SetOnDataChange([generateImage]()
                             { generateImage(); });

  imagePreview->SetOnImageChange([outElement]()
                                 { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([imagePreview, outElement]()
                          { outElement->UpdateData(imagePreview->GetImageData()); });

  generateImage();
  return node;
}
