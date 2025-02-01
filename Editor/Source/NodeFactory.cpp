#include "NodeFactory.h"
#include "GUI/Components/Canvas2D/NodeElements/OutputConnector.h"
#include "GUI/Components/Canvas2D/NodeElements/NodeTypes.h"
#include "Generators/Generators.h"
#include "Generators/RandomNumbers.h"
#include "Core/Logger/Logger.h"

#include <future>
#include <type_traits>

static TextureGenEngine::Node* SpawnNode(TextureGenEngine::Canvas2D *canvas, std::string title)
{
    float x, y;
    canvas->GetSpawnLocation(x, y);
    TextureGenEngine::Node *node = new TextureGenEngine::Node(x, y);
    canvas->AddNode(node);
    node->SetBackground(TextureGenEngine::Color(0.0f, 0.0f, 0.0f, 1.0f));
    node->SetTitle(title);
    return node;
};

static TextureGenEngine::OutputConnector* SetOutputConnector(TextureGenEngine::Node *node, TextureGenEngine::NodeDataTypes type)
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

TextureGenEngine::Node *NodeFactory::TextNode(TextureGenEngine::Canvas2D *canvas, std::string title)
{
    TextureGenEngine::Node* node = SpawnNode(canvas, title);


    TextureGenEngine::TextualInputElement *textInput = AddNodeElement<TextureGenEngine::TextualInputElement>(node);

    TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::TEXT);

    textInput->SetOnDataChange([outElement]()
                               { outElement->TriggerUpdate(); });

    outElement->SetOnUpdate([textInput,outElement]()
                            {
        std::string text = "";
        textInput->GetData(text);
        outElement->UpdateData(text); });

    return node;
}

TextureGenEngine::Node *NodeFactory::TextMergeNode(TextureGenEngine::Canvas2D *canvas, std::string title)
{
    TextureGenEngine::Node *node = SpawnNode(canvas, title);

    TextureGenEngine::TextualInputElement* textFirst = AddNodeElement<TextureGenEngine::TextualInputElement>(node);
    TextureGenEngine::TextualInputElement* textSecond = AddNodeElement<TextureGenEngine::TextualInputElement>(node);

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

TextureGenEngine::Node *NodeFactory::IntegerNode(TextureGenEngine::Canvas2D *canvas, std::string title){
    float x,y;
    canvas->GetSpawnLocation(x,y);
}



TextureGenEngine::Node *NodeFactory::NoiseGenImage(TextureGenEngine::Canvas2D *canvas, std::string title)
{
    TextureGenEngine::Node* node = SpawnNode(canvas, title);
    TextureGenEngine::FloatInputElement *frequencyInput = AddNodeElement<TextureGenEngine::FloatInputElement>(node);
    TextureGenEngine::IntegerElement *seedInput = AddNodeElement<TextureGenEngine::IntegerElement>(node);
    TextureGenEngine::ImagePreviewElement *imagePreview = AddNodeElement<TextureGenEngine::ImagePreviewElement>(node);
    TextureGenEngine::OutputConnector *outElement = SetOutputConnector(node, TextureGenEngine::NodeDataTypes::PatternGenerator);



    frequencyInput->SetData(0.1f);
    seedInput->SetData(TextureGenEngine::Random::RandInt(0, 1000000));

    imagePreview->SetImageSize(100, 100);


    frequencyInput->SetOnDataChange([outElement]()
                         { outElement->TriggerUpdate(); });

    seedInput->SetOnDataChange([outElement]()
                         { outElement->TriggerUpdate(); });

    


    outElement->SetOnUpdate([frequencyInput, seedInput, imagePreview, outElement]()
                            {
                                int seed;
                                float frequency;
                                frequencyInput->GetData(frequency);
                                seedInput->GetData(seed);
                                TextureGenEngine::PatternGenerator::Perlin::GenTileable2D(imagePreview->GetImageDataPtr(), imagePreview->GetImageWidth(), imagePreview->GetImageHeight(), frequency, seed);
                                imagePreview->UpdateImage();
                            });


    outElement->TriggerUpdate();
    return node;
}
