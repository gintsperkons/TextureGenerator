#pragma once
#include <string>
#include <GUI/Components/Canvas2D/Node.h>
#include <GUI/Components/Canvas2D/Canvas2D.h>
#include <GUI/Components/Canvas2D/NodeElements/NodeElements.h>
namespace NodeFactory
{   
    // base nodes
    TextureGenEngine::Node *TextNode(TextureGenEngine::Canvas2D *canvas, std::string title);
    TextureGenEngine::Node *TextMergeNode(TextureGenEngine::Canvas2D *canvas, std::string title);
    TextureGenEngine::Node *IntegerNode(TextureGenEngine::Canvas2D *canvas, std::string title);
    TextureGenEngine::Node *FloatNode(TextureGenEngine::Canvas2D *canvas, std::string title);
    
    // math nodes
    TextureGenEngine::Node *AddIntNode(TextureGenEngine::Canvas2D *canvas, std::string title);
    TextureGenEngine::Node *SubtractIntNode(TextureGenEngine::Canvas2D *canvas, std::string title);
    TextureGenEngine::Node *MultiplyIntNode(TextureGenEngine::Canvas2D *canvas, std::string title);
    TextureGenEngine::Node *DivideIntNode(TextureGenEngine::Canvas2D *canvas, std::string title);
    
    TextureGenEngine::Node *AddFloatNode(TextureGenEngine::Canvas2D *canvas, std::string title);
    TextureGenEngine::Node *SubtractFloatNode(TextureGenEngine::Canvas2D *canvas, std::string title);
    TextureGenEngine::Node *MultiplyFloatNode(TextureGenEngine::Canvas2D *canvas, std::string title);
    TextureGenEngine::Node *DivideFloatNode(TextureGenEngine::Canvas2D *canvas, std::string title);

    
    // pattern generation nodes
    TextureGenEngine::Node *NoiseGenImage(TextureGenEngine::Canvas2D *canvas, std::string title);
} // namespace NodeFactory
