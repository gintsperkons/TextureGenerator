#pragma once
#include <string>
#include <GUI/Components/Canvas2D/Node.h>
#include <GUI/Components/Canvas2D/Canvas2D.h>
#include <GUI/Components/Canvas2D/NodeElements/NodeElements.h>
namespace NodeFactory
{
  enum class NodeType
  {
    NONE,
    TEXT,
    TEXT_MERGE,
    INTEGER,
    FLOAT,
    ADD_INT,
    SUBTRACT_INT,
    MULTIPLY_INT,
    DIVIDE_INT,
    ADD_FLOAT,
    SUBTRACT_FLOAT,
    MULTIPLY_FLOAT,
    DIVIDE_FLOAT,
    PERLIN_GEN_IMAGE,
    CELLULAR_GEN_IMAGE,
    OUTPUT,
    MERGE_IMAGE_BY_FLOAT
  };
  struct NodeTypeCompare
  {

    bool operator()(const NodeType &lhs, const NodeType &rhs) const

    {

      return static_cast<int>(lhs) < static_cast<int>(rhs);
    }
  };

  // output nodes
  TextureGenEngine::Node *
  OutputNode(TextureGenEngine::Canvas2D *canvas, std::string title = "Export Image", int x = 0, int y = 0);

  // base nodes
  TextureGenEngine::Node *TextNode(TextureGenEngine::Canvas2D *canvas, std::string title = "Text", int x = 0, int y = 0);
  TextureGenEngine::Node *TextMergeNode(TextureGenEngine::Canvas2D *canvas, std::string title = "Text Merge", int x = 0, int y = 0);
  TextureGenEngine::Node *IntegerNode(TextureGenEngine::Canvas2D *canvas, std::string title = "Integer", int x = 0, int y = 0);
  TextureGenEngine::Node *FloatNode(TextureGenEngine::Canvas2D *canvas, std::string title = "Float", int x = 0, int y = 0);

  // math nodes
  TextureGenEngine::Node *AddIntNode(TextureGenEngine::Canvas2D *canvas, std::string title = "Perlin Gen", int x = 0, int y = 0);
  TextureGenEngine::Node *SubtractIntNode(TextureGenEngine::Canvas2D *canvas, std::string title = "Add Int", int x = 0, int y = 0);
  TextureGenEngine::Node *MultiplyIntNode(TextureGenEngine::Canvas2D *canvas, std::string title = "Subtract Int", int x = 0, int y = 0);
  TextureGenEngine::Node *DivideIntNode(TextureGenEngine::Canvas2D *canvas, std::string title = "Multiply Int", int x = 0, int y = 0);

  TextureGenEngine::Node *AddFloatNode(TextureGenEngine::Canvas2D *canvas, std::string title = "Divide Int", int x = 0, int y = 0);
  TextureGenEngine::Node *SubtractFloatNode(TextureGenEngine::Canvas2D *canvas, std::string title = "Add Float", int x = 0, int y = 0);
  TextureGenEngine::Node *MultiplyFloatNode(TextureGenEngine::Canvas2D *canvas, std::string title = "Subtract Float", int x = 0, int y = 0);
  TextureGenEngine::Node *DivideFloatNode(TextureGenEngine::Canvas2D *canvas, std::string title = "Multiply Float", int x = 0, int y = 0);

  // pattern generation nodes
  TextureGenEngine::Node *PerlinGenImage(TextureGenEngine::Canvas2D *canvas, std::string title = "Divide Float", int x = 0, int y = 0);
  TextureGenEngine::Node *CellularGenImage(TextureGenEngine::Canvas2D *canvas, std::string title = "Divide Float", int x = 0, int y = 0);

  // Image Manipulation nodes
  TextureGenEngine::Node *MergeImageByFloat(TextureGenEngine::Canvas2D* canvas, std::string title = "Merge With Float",int x = 0, int y = 0);
} // namespace NodeFactory
