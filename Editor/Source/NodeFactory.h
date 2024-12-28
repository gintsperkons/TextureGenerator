#pragma once
#include <string>
#include <GUI/Components/Canvas2D/Node.h>
#include <GUI/Components/Canvas2D/Canvas2D.h>
#include <GUI/Components/Canvas2D/NodeElements/NodeElements.h>
namespace NodeFactory
{
    TextureGenEngine::Node* TextNode(TextureGenEngine::Canvas2D* canvas, std::string title);
    TextureGenEngine::Node* TextMergeNode(TextureGenEngine::Canvas2D* canvas, std::string title);
} // namespace NodeFactory
