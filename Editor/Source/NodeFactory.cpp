#include "NodeFactory.h"
#include "GUI/Components/Canvas2D/NodeElements/OutputConnector.h"
#include "GUI/Components/Canvas2D/NodeElements/NodeTypes.h"
#include "Core/Logger/Logger.h"

TextureGenEngine::Node *NodeFactory::TextNode(TextureGenEngine::Canvas2D *canvas, std::string title)
{
    float x, y;
    canvas->GetSpawnLocation(x, y);
    TextureGenEngine::Node *node = new TextureGenEngine::Node(x, y);
    canvas->AddNode(node);
    node->SetBackground(TextureGenEngine::Color(0.0f, 0.0f, 0.0f, 1.0f));
    node->SetTitle(title);

    TextureGenEngine::TextualInputElement *intElement = new TextureGenEngine::TextualInputElement();
    intElement->SetBackground(TextureGenEngine::Color(0.0f, 0.0f, 0.0f, 0.0f));
    node->AddElement(intElement);

    TextureGenEngine::OutputConnector *outElement = new TextureGenEngine::OutputConnector();
    outElement->SetDataType(TextureGenEngine::NodeDataTypes::TEXT);
    node->SetOutput(outElement);

    intElement->SetOnDataChange([out = outElement]()
                                { out->TriggerUpdate(); });

    outElement->SetOnUpdate([el1 = intElement, out = outElement]()
                            {
        std::string text = "";
        el1->GetData(text);
        out->UpdateData(text); });

    return node;
}

TextureGenEngine::Node *NodeFactory::TextMergeNode(TextureGenEngine::Canvas2D *canvas, std::string title)
{
    float x, y;
    canvas->GetSpawnLocation(x, y);
    TextureGenEngine::Node *node = new TextureGenEngine::Node(x, y);
    canvas->AddNode(node);
    node->SetBackground(TextureGenEngine::Color(0.0f, 0.0f, 0.0f, 1.0f));
    node->SetTitle(title);

    TextureGenEngine::TextualInputElement *el1 = new TextureGenEngine::TextualInputElement();
    el1->SetBackground(TextureGenEngine::Color(0.0f, 0.0f, 0.0f, 0.0f));
    TextureGenEngine::TextualInputElement *el2 = new TextureGenEngine::TextualInputElement();
    el2->SetBackground(TextureGenEngine::Color(0.0f, 0.0f, 0.0f, 0.0f));

    node->AddElement(el1);
    node->AddElement(el2);

    TextureGenEngine::OutputConnector *outElement = new TextureGenEngine::OutputConnector();
    outElement->SetDataType(TextureGenEngine::NodeDataTypes::TEXT);
    node->SetOutput(outElement);

    el1->SetOnDataChange([out = outElement]()
                         { out->TriggerUpdate(); });

    el2->SetOnDataChange([out = outElement]()
                         { out->TriggerUpdate(); });

    outElement->SetOnUpdate([el1 = el1, el2 = el2, out = outElement]()
                            {
                                std::string text1 = "";
                                std::string text2 = "";
                                el1->GetData(text1);    
                                el2->GetData(text2);
                                out->UpdateData(text1 + text2); });

    return node;
}

TextureGenEngine::Node *NodeFactory::NoiseGenImage(TextureGenEngine::Canvas2D *canvas, std::string title)
{
    float x, y;
    canvas->GetSpawnLocation(x, y);
    TextureGenEngine::Node *node = new TextureGenEngine::Node(x, y);
    canvas->AddNode(node);
    node->SetBackground(TextureGenEngine::Color(0.0f, 0.0f, 0.0f, 1.0f));
    node->SetTitle(title);

    TextureGenEngine::FloatInputElement *el1 = new TextureGenEngine::FloatInputElement();
    el1->SetBackground(TextureGenEngine::Color(0.0f, 0.0f, 0.0f, 0.0f));
    node->AddElement(el1);

    TextureGenEngine::IntegerElement *el2 = new TextureGenEngine::IntegerElement();
    el2->SetBackground(TextureGenEngine::Color(0.0f, 0.0f, 0.0f, 0.0f));
    node->AddElement(el2);

    TextureGenEngine::ImagePreviewElement *el3 = new TextureGenEngine::ImagePreviewElement();
    el3->SetBackground(TextureGenEngine::Color(0.0f, 0.0f, 0.0f, 1.0f));
    node->AddElement(el3);
    float frequency;
    int seed;
    el3->GetFrequency(frequency);
    el3->GetSeed(seed);
    el1->SetData(frequency);
    el2->SetData(seed);

    el1->SetOnDataChange([el3 = el3, el1 = el1]()
                         {
                             float frequency;
                             el1->GetData(frequency);
                             el3->SetFrequency(frequency);
                         });
    
    el2 ->SetOnDataChange([el3 = el3, el2 = el2]()
                         {
                             int seed;
                             el2->GetData(seed);
                             el3->SetSeed(seed);
                         });



    TextureGenEngine::OutputConnector *outElement = new TextureGenEngine::OutputConnector();
    outElement->SetDataType(TextureGenEngine::NodeDataTypes::IMAGE);
    node->SetOutput(outElement);

    return node;
}
