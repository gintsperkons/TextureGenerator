#include "NodeFactory.h"
#include "GUI/Components/Canvas2D/NodeElements/OutputConnector.h"
#include "GUI/Components/Canvas2D/NodeElements/NodeTypes.h"

TextureGenEngine::Node *NodeFactory::TextNode(TextureGenEngine::Canvas2D* canvas, std::string title)
{
    float x, y;
    canvas->GetSpawnLocation(x,y);
    TextureGenEngine::Node *node = new TextureGenEngine::Node(x,y);
    canvas->AddNode(node);
    node->SetBackground(TextureGenEngine::Color(0.0f, 0.0f, 0.0f, 1.0f));
    node->SetTitle(title);

    TextureGenEngine::TextualInputElement *intElement = new TextureGenEngine::TextualInputElement();
    intElement->SetBackground(TextureGenEngine::Color(0.0f, 0.0f, 0.0f, 0.0f));
    node->AddElement(intElement);

    TextureGenEngine::OutputConnector *outElement = new TextureGenEngine::OutputConnector();
    outElement->SetDataType(TextureGenEngine::NodeDataTypes::TEXT);
    node->SetOutput(outElement);

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

    return node;
}
