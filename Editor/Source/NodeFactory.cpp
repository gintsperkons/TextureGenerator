#include "NodeFactory.h"
#include "GUI/Components/Canvas2D/NodeElements/OutputConnector.h"
#include "GUI/Components/Canvas2D/NodeElements/NodeTypes.h"
#include "Generators/Generators.h"
#include "Generators/RandomNumbers.h"
#include "Core/Logger/Logger.h"
#include "GUI/Components/Canvas2D/NodeElements/NodeTypes.h"
#include "Core/Renderer/TextureData.h"
#include "ImageJobQueue.h"
#include <future>
#include <type_traits>
#include <mutex>

static const int c_imageSize = 2048;
static ImageJobQueue imageWorkerQueue = ImageJobQueue();


static  void ConvertNormalFloatToChar(std::vector<float> &data, TextureGenEngine::ImagePreviewElement *imagePreview) {
  TextureGenEngine::TextureData *textureData = imagePreview->GetImageData();
  for (int i = 0; i < data.size(); i++)
  {
    int color = static_cast<int>((data[i] + 1.f) * 127.5f);
    textureData->SetPixel(i % imagePreview->GetImageWidth(), i / imagePreview->GetImageWidth(), color, color, color, 255);
  }
  imagePreview->SetTextureData(textureData);
}

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
  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::IMAGE );

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
                              std::vector<float> data(imagePreview->GetImageWidth() * imagePreview->GetImageHeight());

                              TextureGenEngine::PatternGenerator::Perlin::GenTileable2D(data.data(), imagePreview->GetImageWidth(), imagePreview->GetImageHeight(), frequency, seed);
                              if (cancelFlag.get()->load())
                                return;
                              ConvertNormalFloatToChar(data, imagePreview);
                                     });
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
  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::IMAGE);

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
                            {
                              if (cancelFlag.get()->load())
                                return;
                              std::vector<float> data(imagePreview->GetImageWidth() * imagePreview->GetImageHeight());

                              TextureGenEngine::PatternGenerator::Cellular::GenTileable2D(data.data(), imagePreview->GetImageWidth(), imagePreview->GetImageHeight(), frequency, seed);
                              if (cancelFlag.get()->load())
                                return;
                              ConvertNormalFloatToChar(data, imagePreview);
                              
                              });
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

TextureGenEngine::Node *NodeFactory::HorizontalLine(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas,title,NodeType::HORIZONTAL_LINES, x,y);

  TextureGenEngine::ImagePreviewElement *imagePreview = AddNodeElement<TextureGenEngine::ImagePreviewElement>(node);
  TextureGenEngine::FloatInputElement *frequencyInput = AddNodeElement<TextureGenEngine::FloatInputElement>(node);
  TextureGenEngine::FloatInputElement *amplitudeInput = AddNodeElement<TextureGenEngine::FloatInputElement>(node);
  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::IMAGE);

  frequencyInput->SetData(5.0f);
  amplitudeInput->SetData(1.0f);

  imagePreview->SetImageSize(c_imageSize, c_imageSize); 

  std::function generateImage = [imagePreview, node, frequencyInput, amplitudeInput]()
  {
    float frequancy, amplitude;
    frequencyInput->GetData(frequancy);
    amplitudeInput->GetData(amplitude);
    imageWorkerQueue.AddJob(node->GetUUID(),[imagePreview,frequancy,amplitude](std::shared_ptr<std::atomic<bool>> cancelFlag)
    {
      if (cancelFlag.get()->load())
        return;
      std::vector<float> data(imagePreview->GetImageWidth() * imagePreview->GetImageHeight());

      TextureGenEngine::PatternGenerator::HorizontalLine::GenTileable2D(data.data(),imagePreview->GetImageWidth(), imagePreview->GetImageHeight(),frequancy,amplitude);
      if (cancelFlag.get()->load())
        return;
      ConvertNormalFloatToChar(data, imagePreview);
                              
    });
  };

  frequencyInput->SetOnDataChange([generateImage]()
                                  { generateImage(); });

  amplitudeInput->SetOnDataChange([generateImage]()
                             { generateImage(); });

  imagePreview->SetOnImageChange([outElement]()
                                 { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([imagePreview, outElement]()
                          { outElement->UpdateData(imagePreview->GetImageData()); 
                          LOG_DEBUG("TEst");});

  generateImage();
  return node;
}

TextureGenEngine::Node *NodeFactory::VerticalLine(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::VERTICAL_LINES, x, y);

  TextureGenEngine::ImagePreviewElement *imagePreview = AddNodeElement<TextureGenEngine::ImagePreviewElement>(node);
  TextureGenEngine::FloatInputElement *frequencyInput = AddNodeElement<TextureGenEngine::FloatInputElement>(node);
  TextureGenEngine::FloatInputElement *amplitudeInput = AddNodeElement<TextureGenEngine::FloatInputElement>(node);
  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::IMAGE);

  frequencyInput->SetData(5.0f);
  amplitudeInput->SetData(1.0f);

  imagePreview->SetImageSize(c_imageSize, c_imageSize);

  std::function generateImage = [imagePreview, node, frequencyInput, amplitudeInput]()
  {
    float frequancy, amplitude;
    frequencyInput->GetData(frequancy);
    amplitudeInput->GetData(amplitude);
    imageWorkerQueue.AddJob(node->GetUUID(), [imagePreview, frequancy, amplitude](std::shared_ptr<std::atomic<bool>> cancelFlag)
                            {
                              if (cancelFlag.get()->load())
                                return;
                              std::vector<float> data(imagePreview->GetImageWidth() * imagePreview->GetImageHeight());

                              TextureGenEngine::PatternGenerator::VerticalLine::GenTileable2D(data.data(), imagePreview->GetImageWidth(), imagePreview->GetImageHeight(), frequancy, amplitude);
                              if (cancelFlag.get()->load())
                                return;
                              ConvertNormalFloatToChar(data, imagePreview);
                            });
  };

  frequencyInput->SetOnDataChange([generateImage]()
                                  { generateImage(); });

  amplitudeInput->SetOnDataChange([generateImage]()
                                  { generateImage(); });

  imagePreview->SetOnImageChange([outElement]()
                                 { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([imagePreview, outElement]()
                          { outElement->UpdateData(imagePreview->GetImageData());  });

  generateImage();
  return node;
}

TextureGenEngine::Node *NodeFactory::CheckerBoard(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::CHECKER_BOARD, x, y);

  TextureGenEngine::ImagePreviewElement *imagePreview = AddNodeElement<TextureGenEngine::ImagePreviewElement>(node);
  TextureGenEngine::FloatInputElement *frequencyInput = AddNodeElement<TextureGenEngine::FloatInputElement>(node);
  TextureGenEngine::FloatInputElement *amplitudeInput = AddNodeElement<TextureGenEngine::FloatInputElement>(node);
  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::IMAGE);

  frequencyInput->SetData(5.0f);
  amplitudeInput->SetData(1.0f);

  imagePreview->SetImageSize(c_imageSize, c_imageSize);

  std::function generateImage = [imagePreview, node, frequencyInput, amplitudeInput]()
  {
    float frequancy, amplitude;
    frequencyInput->GetData(frequancy);
    amplitudeInput->GetData(amplitude);
    imageWorkerQueue.AddJob(node->GetUUID(), [imagePreview, frequancy, amplitude](std::shared_ptr<std::atomic<bool>> cancelFlag)
                            {
                              if (cancelFlag.get()->load())
                                return;
                              std::vector<float> data(imagePreview->GetImageWidth() * imagePreview->GetImageHeight());

                              TextureGenEngine::PatternGenerator::CheckerBoard::GenTileable2D(data.data(), imagePreview->GetImageWidth(), imagePreview->GetImageHeight(), frequancy, amplitude);
                              if (cancelFlag.get()->load())
                                return;
                              ConvertNormalFloatToChar(data, imagePreview); });
  };

  frequencyInput->SetOnDataChange([generateImage]()
                                  { generateImage(); });

  amplitudeInput->SetOnDataChange([generateImage]()
                                  { generateImage(); });

  imagePreview->SetOnImageChange([outElement]()
                                 { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([imagePreview, outElement]()
                          { outElement->UpdateData(imagePreview->GetImageData()); });

  generateImage();
  return node;
}

TextureGenEngine::Node *NodeFactory::MergeImageByFloat(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::MERGE_IMAGE_BY_FLOAT, x, y);

  TextureGenEngine::ImageInputElement *imageInput1 = AddNodeElement<TextureGenEngine::ImageInputElement>(node);
  TextureGenEngine::ImageInputElement *imageInput2 = AddNodeElement<TextureGenEngine::ImageInputElement>(node);
  TextureGenEngine::FloatInputElement *floatInput = AddNodeElement<TextureGenEngine::FloatInputElement>(node);
  TextureGenEngine::ImagePreviewElement *imagePreview = AddNodeElement<TextureGenEngine::ImagePreviewElement>(node);

  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::IMAGE);

  imagePreview->SetImageSize(c_imageSize, c_imageSize);



  std::function mergeImage = [imageInput1, imageInput2, floatInput, imagePreview, node]()
  {
    imagePreview->LoadingScreen();
    imageWorkerQueue.AddJob(node->GetUUID(), [imagePreview, imageInput1, imageInput2, floatInput](std::shared_ptr<std::atomic<bool>> cancelFlag)
                            {
                              if (cancelFlag.get()->load())
                                return;
                              float factor;
                              floatInput->GetData(factor);
                              TextureGenEngine::TextureData *textureData = imagePreview->GetImageData();

                              textureData->MergeByFloat(imageInput1->GetData(), imageInput2->GetData(), factor);
                              if (cancelFlag.get()->load())
                                return;
                              imagePreview->SetTextureData(textureData);
                            });
  };

  imageInput1->SetOnDataChange([mergeImage]()
                               { mergeImage(); });
  imageInput2->SetOnDataChange([mergeImage]()
                               { mergeImage(); });
  floatInput->SetOnDataChange([mergeImage]()
                              { mergeImage(); });

  imagePreview->SetOnImageChange([outElement]()
                                 { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([imagePreview, outElement]()
                          { outElement->UpdateData(imagePreview->GetImageData()); });

  return node;
}

TextureGenEngine::Node *NodeFactory::MergeImageByImage(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::MERGE_IMAGE_BY_FLOAT, x, y);

  TextureGenEngine::ImageInputElement *imageInput1 = AddNodeElement<TextureGenEngine::ImageInputElement>(node);
  TextureGenEngine::ImageInputElement *imageInput2 = AddNodeElement<TextureGenEngine::ImageInputElement>(node);
  TextureGenEngine::ImageInputElement *imageInput3 = AddNodeElement<TextureGenEngine::ImageInputElement>(node);
  TextureGenEngine::ImagePreviewElement *imagePreview = AddNodeElement<TextureGenEngine::ImagePreviewElement>(node);

  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::IMAGE);

  imagePreview->SetImageSize(c_imageSize, c_imageSize);

  std::function mergeImage = [imageInput1, imageInput2, imageInput3, imagePreview, node]()
  {
    imagePreview->LoadingScreen();
    imageWorkerQueue.AddJob(node->GetUUID(), [imagePreview, imageInput1, imageInput2, imageInput3](std::shared_ptr<std::atomic<bool>> cancelFlag)
                            {
                              if (cancelFlag.get()->load())
                                return;
                              TextureGenEngine::TextureData *textureData = imagePreview->GetImageData();

                              textureData->MergeByImage(imageInput1->GetData(), imageInput2->GetData(), imageInput3->GetData());
                              if (cancelFlag.get()->load())
                                return;
                              imagePreview->SetTextureData(textureData); });
  };

  imageInput1->SetOnDataChange([mergeImage]()
                               { mergeImage(); });
  imageInput2->SetOnDataChange([mergeImage]()
                               { mergeImage(); });
  imageInput3->SetOnDataChange([mergeImage]()
                               { mergeImage(); });

  imagePreview->SetOnImageChange([outElement]()
                                 { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([imagePreview, outElement]()
                          { outElement->UpdateData(imagePreview->GetImageData()); });

  return node;
}

TextureGenEngine::Node *NodeFactory::BinaryThreshold(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::BINARY_THRESHOLD, x, y);

  TextureGenEngine::ImageInputElement *imageInput = AddNodeElement<TextureGenEngine::ImageInputElement>(node);
  TextureGenEngine::IntegerElement *thresholdInput = AddNodeElement<TextureGenEngine::IntegerElement>(node);
  TextureGenEngine::ImagePreviewElement *imagePreview = AddNodeElement<TextureGenEngine::ImagePreviewElement>(node);

  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::IMAGE);

  imagePreview->SetImageSize(c_imageSize, c_imageSize);
  
  std::function binaryThreshold = [imageInput, thresholdInput, imagePreview, node]()
  {
    imagePreview->LoadingScreen();
    imageWorkerQueue.AddJob(node->GetUUID(), [imagePreview, imageInput, thresholdInput](std::shared_ptr<std::atomic<bool>> cancelFlag)
                            {
                              if (cancelFlag.get()->load())
                                return;
                              int threshold;
                              thresholdInput->GetData(threshold);
                              TextureGenEngine::TextureData *textureData = imagePreview->GetImageData();

                              textureData->BinaryThreshold(imageInput->GetData(), threshold);
                              if (cancelFlag.get()->load())
                                return;
                              imagePreview->SetTextureData(textureData); 
                            });
  };

  imageInput->SetOnDataChange([binaryThreshold]()
                              { binaryThreshold(); });
  thresholdInput->SetOnDataChange([binaryThreshold]()
                                  { binaryThreshold(); });

  imagePreview->SetOnImageChange([outElement]()
                                 { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([imagePreview, outElement]()
                          { outElement->UpdateData(imagePreview->GetImageData()); });

  return node;
}

TextureGenEngine::Node *NodeFactory::MaskImage(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::MASK_IMAGE, x, y);

  TextureGenEngine::ImageInputElement *imageInput = AddNodeElement<TextureGenEngine::ImageInputElement>(node);
  TextureGenEngine::ImageInputElement *maskInput = AddNodeElement<TextureGenEngine::ImageInputElement>(node);
  TextureGenEngine::ImagePreviewElement *imagePreview = AddNodeElement<TextureGenEngine::ImagePreviewElement>(node);

  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::IMAGE);

  imagePreview->SetImageSize(c_imageSize, c_imageSize);

  std::function maskImage = [imageInput, maskInput, imagePreview, node]()
  {
    imagePreview->LoadingScreen();
    imageWorkerQueue.AddJob(node->GetUUID(), [imagePreview, imageInput, maskInput](std::shared_ptr<std::atomic<bool>> cancelFlag)
                            {
                              if (cancelFlag.get()->load())
                                return;
                              TextureGenEngine::TextureData *textureData = imagePreview->GetImageData();

                              textureData->Mask(imageInput->GetData(), maskInput->GetData());
                              if (cancelFlag.get()->load())
                                return;
                              imagePreview->SetTextureData(textureData);
                            });
  };

  imageInput->SetOnDataChange([maskImage]()
                              { maskImage(); });
  maskInput->SetOnDataChange([maskImage]()
                             { maskImage(); });

  imagePreview->SetOnImageChange([outElement]()
                                 { outElement->TriggerUpdate(); });   

  outElement->SetOnUpdate([imagePreview, outElement]()
                          { outElement->UpdateData(imagePreview->GetImageData()); }); 

  return node;  
}

TextureGenEngine::Node *NodeFactory::InvertImage(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::INVERT_IMAGE, x, y);

  TextureGenEngine::ImageInputElement *imageInput = AddNodeElement<TextureGenEngine::ImageInputElement>(node);
  TextureGenEngine::ImagePreviewElement *imagePreview = AddNodeElement<TextureGenEngine::ImagePreviewElement>(node);

  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::IMAGE);

  imagePreview->SetImageSize(c_imageSize, c_imageSize);

  std::function invertImage = [imageInput, imagePreview, node]()
  {
    imagePreview->LoadingScreen();
    imageWorkerQueue.AddJob(node->GetUUID(), [imagePreview, imageInput](std::shared_ptr<std::atomic<bool>> cancelFlag)
                            {
                              if (cancelFlag.get()->load())
                                return;
                              TextureGenEngine::TextureData *textureData = imagePreview->GetImageData();

                              textureData->Invert(imageInput->GetData());
                              if (cancelFlag.get()->load())
                                return;
                              imagePreview->SetTextureData(textureData);
                            });
  };

  imageInput->SetOnDataChange([invertImage]()
                              { invertImage(); });          

  imagePreview->SetOnImageChange([outElement]()
                                 { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([imagePreview, outElement]()
                          { outElement->UpdateData(imagePreview->GetImageData()); });

  return node;
}

TextureGenEngine::Node *NodeFactory::DialateImage(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::BINARY_THRESHOLD, x, y);

  TextureGenEngine::ImageInputElement *imageInput = AddNodeElement<TextureGenEngine::ImageInputElement>(node);
  TextureGenEngine::IntegerElement *sizeInput = AddNodeElement<TextureGenEngine::IntegerElement>(node);
  TextureGenEngine::ImagePreviewElement *imagePreview = AddNodeElement<TextureGenEngine::ImagePreviewElement>(node);

  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::IMAGE);

  imagePreview->SetImageSize(c_imageSize, c_imageSize);

  std::function dialateImage = [imageInput, sizeInput, imagePreview, node]()
  {
    imagePreview->LoadingScreen();
    imageWorkerQueue.AddJob(node->GetUUID(), [imagePreview, imageInput, sizeInput](std::shared_ptr<std::atomic<bool>> cancelFlag)
                            {
                              if (cancelFlag.get()->load())
                                return;
                              int size;
                              sizeInput->GetData(size);
                              TextureGenEngine::TextureData *textureData = imagePreview->GetImageData();

                              textureData->Dialate(imageInput->GetData(), size);
                              if (cancelFlag.get()->load())
                                return;
                              imagePreview->SetTextureData(textureData); });
  };

  imageInput->SetOnDataChange([dialateImage]()
                              { dialateImage(); });
  sizeInput->SetOnDataChange([dialateImage]()
                                  { dialateImage(); });

  imagePreview->SetOnImageChange([outElement]()
                                 { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([imagePreview, outElement]()
                          { outElement->UpdateData(imagePreview->GetImageData()); });

  return node;
}

TextureGenEngine::Node * NodeFactory::ErodeImage(TextureGenEngine::Canvas2D * canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::BINARY_THRESHOLD, x, y);

  TextureGenEngine::ImageInputElement *imageInput = AddNodeElement<TextureGenEngine::ImageInputElement>(node);
  TextureGenEngine::IntegerElement *sizeInput = AddNodeElement<TextureGenEngine::IntegerElement>(node);
  TextureGenEngine::ImagePreviewElement *imagePreview = AddNodeElement<TextureGenEngine::ImagePreviewElement>(node);

  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::IMAGE);

  imagePreview->SetImageSize(c_imageSize, c_imageSize);

  std::function erodeImage = [imageInput, sizeInput, imagePreview, node]()
  {
    imagePreview->LoadingScreen();
    imageWorkerQueue.AddJob(node->GetUUID(), [imagePreview, imageInput, sizeInput](std::shared_ptr<std::atomic<bool>> cancelFlag)
                            {
                              if (cancelFlag.get()->load())
                                return;
                              int size;
                              sizeInput->GetData(size);
                              TextureGenEngine::TextureData *textureData = imagePreview->GetImageData();

                              textureData->Erode(imageInput->GetData(), size);
                              if (cancelFlag.get()->load())
                                return;
                              imagePreview->SetTextureData(textureData); });
  };

  imageInput->SetOnDataChange([erodeImage]()
                              { erodeImage(); });
  sizeInput->SetOnDataChange([erodeImage]()
                             { erodeImage(); });

  imagePreview->SetOnImageChange([outElement]()
                                 { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([imagePreview, outElement]()
                          { outElement->UpdateData(imagePreview->GetImageData()); });

  return node;
}

TextureGenEngine::Node *NodeFactory::ColorNode(TextureGenEngine::Canvas2D *canvas, std::string title, int x, int y)
{
  TextureGenEngine::Node *node = SpawnNode(canvas, title, NodeType::COLOR_BASE, x, y);

  TextureGenEngine::IntegerElement *redInput = AddNodeElement<TextureGenEngine::IntegerElement>(node);
  TextureGenEngine::IntegerElement *greenInput = AddNodeElement<TextureGenEngine::IntegerElement>(node);
  TextureGenEngine::IntegerElement *blueInput = AddNodeElement<TextureGenEngine::IntegerElement>(node);
  TextureGenEngine::IntegerElement *alphaInput = AddNodeElement<TextureGenEngine::IntegerElement>(node);
  TextureGenEngine::ImagePreviewElement *imagePreview = AddNodeElement<TextureGenEngine::ImagePreviewElement>(node);  

  redInput->SetData(255);
  greenInput->SetData(255);
  blueInput->SetData(255);
  alphaInput->SetData(255);

  TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::IMAGE);

  imagePreview->SetImageSize(c_imageSize, c_imageSize);

  std::function colorImage = [redInput, greenInput, blueInput, alphaInput, imagePreview, node]()
  {
    imagePreview->LoadingScreen();
    imageWorkerQueue.AddJob(node->GetUUID(), [imagePreview, redInput, greenInput, blueInput, alphaInput](std::shared_ptr<std::atomic<bool>> cancelFlag)
                            {
                              if (cancelFlag.get()->load())
                                return;
                              TextureGenEngine::TextureData *textureData = imagePreview->GetImageData();

                              textureData->Color(redInput->GetData(), greenInput->GetData(), blueInput->GetData(), alphaInput->GetData());
                              if (cancelFlag.get()->load())
                                return;
                              imagePreview->SetTextureData(textureData);                              
                            });
  };

  redInput->SetOnDataChange([colorImage]()
                            { colorImage(); });
  greenInput->SetOnDataChange([colorImage]()
                              { colorImage(); });
  blueInput->SetOnDataChange([colorImage]()
                             { colorImage(); });
  alphaInput->SetOnDataChange([colorImage]()
                              { colorImage(); });

  imagePreview->SetOnImageChange([outElement]()
                                 { outElement->TriggerUpdate(); });

  outElement->SetOnUpdate([imagePreview, outElement]()
                          { outElement->UpdateData(imagePreview->GetImageData()); });

  colorImage();

  return node;
}
