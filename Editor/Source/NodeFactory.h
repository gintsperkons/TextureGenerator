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
    MERGE_IMAGE_BY_FLOAT,
    BINARY_THRESHOLD,
    MASK_IMAGE,
    INVERT_IMAGE,
    COLOR_BASE,
    ROTATE_LINE,
    HORIZONTAL_LINES,
    VERTICAL_LINES,
    CHECKER_BOARD,
    MERGE_IMAGE_BY_IMAGE,
    ERODE,
    DIALATE,
    MAP_TO_RED,
    MAP_TO_GREEN,
    MAP_TO_BLUE,
    CIRCLE_GRID

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
  TextureGenEngine::Node *ColorNode(TextureGenEngine::Canvas2D *canvas, std::string title = "Color", int x = 0, int y = 0);

  TextureGenEngine::Node *AddFloatNode(TextureGenEngine::Canvas2D *canvas, std::string title = "Divide Int", int x = 0, int y = 0);
  TextureGenEngine::Node *SubtractFloatNode(TextureGenEngine::Canvas2D *canvas, std::string title = "Add Float", int x = 0, int y = 0);
  TextureGenEngine::Node *MultiplyFloatNode(TextureGenEngine::Canvas2D *canvas, std::string title = "Subtract Float", int x = 0, int y = 0);
  TextureGenEngine::Node *DivideFloatNode(TextureGenEngine::Canvas2D *canvas, std::string title = "Multiply Float", int x = 0, int y = 0);

  // pattern generation nodes
  TextureGenEngine::Node *PerlinGenImage(TextureGenEngine::Canvas2D *canvas, std::string title = "Perlin Noise", int x = 0, int y = 0);
  TextureGenEngine::Node *CellularGenImage(TextureGenEngine::Canvas2D *canvas, std::string title = "Cellular Noise", int x = 0, int y = 0);

  //Math Pattern Generators
  TextureGenEngine::Node *GenLine(TextureGenEngine::Canvas2D *canvas, std::string title = "Line", int x = 0, int y = 0);
  TextureGenEngine::Node *GenCircleGrid(TextureGenEngine::Canvas2D *canvas, std::string title = "Hex Grid", int x = 0, int y = 0);
  TextureGenEngine::Node *HorizontalLine(TextureGenEngine::Canvas2D *canvas, std::string title = "Horizontal Line", int x = 0, int y = 0);
  TextureGenEngine::Node *VerticalLine(TextureGenEngine::Canvas2D *canvas, std::string title = "Vertical Line", int x = 0, int y = 0);
  TextureGenEngine::Node *CheckerBoard(TextureGenEngine::Canvas2D *canvas, std::string title = "Checker Board", int x = 0, int y = 0);

  // Image Manipulation nodes
  TextureGenEngine::Node *MergeImageByFloat(TextureGenEngine::Canvas2D *canvas, std::string title = "Merge With Float", int x = 0, int y = 0);
  TextureGenEngine::Node *MergeImageByImage(TextureGenEngine::Canvas2D *canvas, std::string title = "Merge With Float", int x = 0, int y = 0);
  TextureGenEngine::Node *BinaryThreshold(TextureGenEngine::Canvas2D* canvas, std::string title = "Binary Threshold",int x = 0, int y = 0);
  TextureGenEngine::Node *MaskImage(TextureGenEngine::Canvas2D* canvas, std::string title = "Mask Image",int x = 0, int y = 0);
  TextureGenEngine::Node *InvertImage(TextureGenEngine::Canvas2D *canvas, std::string title = "Invert Image", int x = 0, int y = 0);
  TextureGenEngine::Node *DialateImage(TextureGenEngine::Canvas2D *canvas, std::string title = "Dialate Image", int x = 0, int y = 0);
  TextureGenEngine::Node *ErodeImage(TextureGenEngine::Canvas2D *canvas, std::string title = "Erode Image", int x = 0, int y = 0);
  TextureGenEngine::Node *MapRed(TextureGenEngine::Canvas2D *canvas, std::string title = "Map To Red", int x = 0, int y = 0);
  TextureGenEngine::Node *MapGreen(TextureGenEngine::Canvas2D *canvas, std::string title = "Map To Green", int x = 0, int y = 0);
  TextureGenEngine::Node *MapBlue(TextureGenEngine::Canvas2D *canvas, std::string title = "Map To Blue", int x = 0, int y = 0);

} // namespace NodeFactory
