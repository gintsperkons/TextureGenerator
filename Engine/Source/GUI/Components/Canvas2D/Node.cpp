#include "Node.h"
#include "Core/Renderer/Mesh.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Logger/Logger.h"
#include "GUI/GUIManager.h"
#include "Core/Window/Window.h"
#include "NodeElements/NodeElement.h"
#include "NodeElements/InputConnector.h"
#include "NodeElements/OutputConnector.h"
#include "GUI/Components/Label.h"
#include "Canvas2D.h"
#include "Generators/RandomNumbers.h"
#include "Core/AssetManager/AssetManager.h"

TextureGenEngine::Node::Node(float x, float y, unsigned int nodeID) : Component(x, y, c_minWidth, c_titleHeight), m_outputImage(nullptr)
{
  m_uuid = Random::UUID();
  m_id = nodeID;
  m_title = new Label(x, y, m_width, c_titleHeight, "Node");
  m_title->SetParent(this);
  m_title->SetManager(m_manager);
  m_background->ChangeColor(.0f, .0f, .0f, 1.0f);
  m_background->SetPosition(m_x + c_titleHeight, m_y);
  m_background->SetSize(m_width - (2 * c_titleHeight));

  m_topLeft = ObjectFactory::CreateSquare(c_titleHeight, c_titleHeight, 0, 0, 0.5, 0.5);
  m_topLeft->SetPosition(m_x, m_y);
  m_topLeft->ChangeShader("maskedColor");
  m_topLeft->ChangeTexture(TextureGenEngine::LoadTexture("CircleMask.png"));
  m_topLeft->ChangeColor(.0f, .0f, .0f, 1.0f);

  m_topRight = ObjectFactory::CreateSquare(c_titleHeight, c_titleHeight, 0.5, 0, 1.0f, 0.5);
  m_topRight->SetPosition(m_x + m_width - c_titleHeight, m_y);
  m_topRight->ChangeShader("maskedColor");
  m_topRight->ChangeTexture(TextureGenEngine::LoadTexture("CircleMask.png"));
  m_topRight->ChangeColor(.0f, .0f, .0f, 1.0f);

  m_bottomCenterBackground = ObjectFactory::CreateSquare(m_width - (2 * c_titleHeight), c_titleHeight);
  m_bottomCenterBackground->SetPosition(m_x, m_y);
  m_bottomCenterBackground->ChangeColor(.0f, .0f, .0f, 1.0f);

  m_bottomCenter = ObjectFactory::CreateSquare(m_width - (2 * c_titleHeight), c_titleHeight - c_borderWidth);
  m_bottomCenter->SetPosition(m_x, m_y);
  m_bottomCenter->ChangeColor(0.28125f, 0.25390625f, 0.25390625f, 1.0f);

  m_dataBackBackground = ObjectFactory::CreateSquare(m_width, 100);
  m_dataBackBackground->ChangeColor(.0f, .0f, .0f, 1.0f);

  m_bottomLeftBackground = ObjectFactory::CreateSquare(c_titleHeight, c_titleHeight, 0, 0.5, 0.5f, 1.0f);
  m_bottomLeftBackground->SetPosition(m_x + m_width - c_titleHeight, m_y);
  m_bottomLeftBackground->ChangeShader("maskedColor");
  m_bottomLeftBackground->ChangeTexture(TextureGenEngine::LoadTexture("CircleMask.png"));
  m_bottomLeftBackground->ChangeColor(.0f, .0f, .0f, 1.0f);

  m_bottomLeft = ObjectFactory::CreateSquare(c_titleHeight - c_borderWidth, c_titleHeight - c_borderWidth, 0, 0.5, 0.5f, 1.0f);
  m_bottomLeft->SetPosition(m_x + m_width - c_titleHeight, m_y);
  m_bottomLeft->ChangeShader("maskedColor");
  m_bottomLeft->ChangeTexture(TextureGenEngine::LoadTexture("CircleMask.png"));
  m_bottomLeft->ChangeColor(0.28125f, 0.25390625f, 0.25390625f, 1.0f);

  m_bottomRightBackground = ObjectFactory::CreateSquare(c_titleHeight, c_titleHeight, 0.5f, 0.5f, 1.0f, 1.0f);
  m_bottomRightBackground->SetPosition(m_x + m_width - c_titleHeight, m_y);
  m_bottomRightBackground->ChangeShader("maskedColor");
  m_bottomRightBackground->ChangeTexture(TextureGenEngine::LoadTexture("CircleMask.png"));
  m_bottomRightBackground->ChangeColor(.0f, .0f, .0f, 1.0f);

  m_bottomRight = ObjectFactory::CreateSquare(c_titleHeight-c_borderWidth, c_titleHeight-c_borderWidth, 0.5f, 0.5f, 1.0f, 1.0f);
  m_bottomRight->SetPosition(m_x + m_width - c_titleHeight, m_y);
  m_bottomRight->ChangeShader("maskedColor");
  m_bottomRight->ChangeTexture(TextureGenEngine::LoadTexture("CircleMask.png"));
  m_bottomRight->ChangeColor(0.28125f, 0.25390625f, 0.25390625f, 1.0f);

  m_dataBackground = ObjectFactory::CreateSquare(m_width - c_borderWidth * 2, 100);
  m_dataBackground->ChangeColor(0.28125f, 0.25390625f, 0.25390625f, 1.0f);
  m_draggable = true;
  m_selectable = true;
  m_type = "Node";
  m_dataBackgroundHeight = 100;
}

void TextureGenEngine::Node::Init(float width, float height)
{
  if (m_parent)
  {
    m_x = m_parent->GetX() + m_x;
    m_y = m_parent->GetY() + m_y;

    m_dataBackground->SetPosition(m_x + c_borderWidth, m_y - m_dataBackgroundHeight);
    m_dataBackBackground->SetPosition(m_x, m_y - m_dataBackgroundHeight);
    m_bottomCenterBackground->SetPosition(m_x + c_titleHeight, m_y - m_dataBackgroundHeight - c_titleHeight);
    m_bottomCenter->SetPosition(m_x + c_titleHeight, m_y - m_dataBackgroundHeight - c_titleHeight+c_borderWidth);
    m_bottomLeftBackground->SetPosition(m_x, m_y - m_dataBackgroundHeight - c_titleHeight);
    m_bottomLeft->SetPosition(m_x + c_borderWidth, m_y - m_dataBackgroundHeight - c_titleHeight + c_borderWidth);

    m_bottomRightBackground->SetPosition(m_x+m_width-c_titleHeight, m_y - m_dataBackgroundHeight - c_titleHeight);
    m_bottomRight->SetPosition(m_x + m_width - c_titleHeight, m_y - m_dataBackgroundHeight - c_titleHeight + c_borderWidth);
  }
  Component::Init(width, height);
  m_background->SetPosition(m_x + c_titleHeight, m_y);

  m_topLeft->SetPosition(m_x, m_y);
  m_topRight->SetPosition(m_x + m_width - c_titleHeight, m_y);
  m_title->SetPosition(m_x + c_titleHeight, m_y);
  m_title->Init(width, height);
  for (auto &element : m_elements)
  {
    element->Init(width, height);
  }
}

void TextureGenEngine::Node::Draw()
{

  Component::Draw();
  m_topLeft->Draw();
  m_topRight->Draw();
  m_dataBackBackground->Draw();
  m_dataBackground->Draw();
  m_bottomCenterBackground->Draw();
  m_bottomCenter->Draw();
  m_bottomLeftBackground->Draw();
  m_bottomRightBackground->Draw();
  m_title->Draw();
  m_bottomLeftBackground->Draw();
  m_bottomRightBackground->Draw();
  m_bottomLeft->Draw();
  m_bottomRight->Draw();
  for (auto &element : m_elements)
  {
    element->Draw();
  }
  if (m_outputImage)
  {
    m_outputImage->Draw();
  }
}

void TextureGenEngine::Node::AddElement(NodeElement *element)
{
  element->SetParent(this);
  element->SetManager(m_manager);
  element->Setup(m_x, m_y);
  element->SetNode(this);
  m_elements.push_back(element);
  float maxWidth = 0;
  float totalHeight = 5;
  for (auto &element : m_elements)
  {
    if (element->GetWidth() > maxWidth)
    {
      maxWidth = element->GetWidth();
    }

    totalHeight += element->GetHeight();
    totalHeight += 5;
  }
  if (maxWidth < c_minWidth)
    maxWidth = c_minWidth;
  LOG_DEBUG("Max width %f\n", maxWidth);
  LOG_DEBUG("Total height %f\n", totalHeight);
  m_scales[0] = maxWidth / m_width;
  m_scales[1] = totalHeight / m_dataBackgroundHeight;
  LOG_DEBUG("Scales %f %f\n", m_scales[0], m_scales[1]);
  LOG_DEBUG("total height %f, height %f\n", totalHeight, m_height);
  m_dataBackground->Scale(m_scales[0], m_scales[1]);
  m_dataBackground->SetPosition(m_x + c_borderWidth, m_y - totalHeight);
  m_dataBackBackground->Scale(m_scales[0], m_scales[1]);
  m_dataBackBackground->SetPosition(m_x, m_y - totalHeight);
  m_bottomCenterBackground->SetPosition(m_x + c_titleHeight, m_y - totalHeight - c_titleHeight);
  m_bottomCenter->SetPosition(m_x + c_titleHeight, m_y - totalHeight - c_titleHeight + c_borderWidth);
  m_bottomLeftBackground->SetPosition(m_x, m_y - totalHeight - c_titleHeight);
  m_bottomLeft->SetPosition(m_x + c_borderWidth, m_y - totalHeight - c_titleHeight + c_borderWidth);

  m_bottomRightBackground->SetPosition(m_x + m_width - c_titleHeight, m_y - totalHeight - c_titleHeight);
  m_bottomRight->SetPosition(m_x + m_width - c_titleHeight, m_y - totalHeight - c_titleHeight + c_borderWidth);

  m_bottomRightBackground->SetPosition(m_x + m_width - c_titleHeight, m_y - totalHeight - c_titleHeight);

  m_background->Scale(m_scales[0], 1);
  m_width = maxWidth;
  m_dataBackgroundHeight = totalHeight;
}

void TAPI TextureGenEngine::Node::SetOutput(OutputConnector *output)
{
  m_outputImage = output;
  m_outputImage->SetParent(this);
  m_outputImage->SetManager(m_manager);
  m_outputImage->SetPosition(m_x + m_width - m_outputImage->GetWidth(), m_y - c_titleHeight / 2 - m_outputImage->GetHeight() / 2);
}

void TextureGenEngine::Node::OnMouseDrag(float x, float y)
{
  Component::OnMouseDrag(x, y);
  m_topLeft->Move(x, y);
  m_topRight->Move(x, y);
  m_dataBackground->Move(x, y);
  m_dataBackBackground->Move(x, y);
  m_bottomCenter->Move(x, y);
  m_bottomCenterBackground->Move(x, y);
  m_bottomRightBackground->Move(x,y);
  m_bottomLeftBackground->Move(x,y);
  m_bottomLeft->Move(x,y);
  m_bottomRight->Move(x,y);
  m_title->Move(x, y);
  if (m_outputImage)
    m_outputImage->Move(x, y);
  for (auto &element : m_elements)
  {
    element->OnMouseDrag(x, y);
  }
}

bool TextureGenEngine::Node::CheckCollision(float x, float y)
{
  float x1 = m_x;
  float x2 = m_x + m_width;
  float y1 = m_y;
  float y2 = m_y + m_height;
  float testX = x;
  float testY = y;

  float oldWidth, oldHeight;
  m_manager->GetOldSize(oldWidth, oldHeight);

  if (testX > x1 && testX < x2 && testY > y1 && testY < y2)
  {
    return true;
  }
  return false;
}

float TextureGenEngine::Node::GetOffset(NodeElement *element)
{
  float offset = c_titleHeight;
  for (auto &el : m_elements)
  {
    if (el == element)
    {
      return offset;
    }
    offset += el->GetHeight() + 5;
  }
  return offset;
}

TextureGenEngine::Component *TextureGenEngine::Node::SelectObject(float x, float y)
{
  for (auto &element : m_elements)
  {
    if (element->CheckCollision(x, y))
    {
      LOG_DEBUG("Selecting element\n");
      Component *subElement = element->SelectObject(x, y);
      if (subElement)
      {
        return subElement;
      }
    }
  }
  if (m_outputImage && m_outputImage->CheckCollision(x, y))
  {
    return m_outputImage;
  }
  if (m_selectable && CheckCollision(x, y))
  {
    return this;
  }
  return nullptr;
}

TextureGenEngine::Node::~Node()
{
  if (m_parent)
  {
    m_parent->RemoveChild(this);
  }
  if (m_title)
  {
    delete m_title;
  }
  for (auto &element : m_elements)
  {
    delete element;
  }
  if (m_dataBackground)
  {
    delete m_dataBackground;
  }
  if (m_dataBackBackground)
  {
    delete m_dataBackBackground;
  }
  if (m_topLeft)
  {
    delete m_topLeft;
  }
  if (m_topRight)
  {
    delete m_topRight;
  }
  if (m_bottomCenter)
  {
    delete m_bottomCenter;
  }
  if (m_bottomLeft)
  {
    delete m_bottomLeft;
  }
  if (m_bottomRight)
  {
    delete m_bottomRight;
  }
  if (m_bottomCenterBackground)
  {
    delete m_bottomCenterBackground;
  }
  if (m_bottomLeftBackground)
  {
    delete m_bottomLeftBackground;
  }
  if (m_bottomRightBackground)
  {
    delete m_bottomRightBackground;
  }
  if (m_outputImage)
  {
    delete m_outputImage;
  }
}

TextureGenEngine::InputConnector *TextureGenEngine::Node::GetInputConnector(float x, float y)
{
  for (auto &element : m_elements)
  {
    InputConnector *input = element->GetInputConnector(x, y);
    if (input)
    {
      return input;
    }
  }
  return nullptr;
}

TextureGenEngine::OutputConnector *TextureGenEngine::Node::GetOutputConnector(float x, float y)
{
  if (m_outputImage && m_outputImage->CheckCollision(x, y))
    return m_outputImage;
  return nullptr;
}

void TextureGenEngine::Node::ConnectInput(Node *outputNode, int inputIndex)
{
  if (inputIndex < m_elements.size())
  {
    m_elements[inputIndex]->ConnectInput(outputNode);
  }
}

void TextureGenEngine::Node::AddElementData(std::string data, int index)
{
  if (index < m_elements.size())
  {
    m_elements[index]->ImportElementData(data);
  }
}

TextureGenEngine::NodeInfo TextureGenEngine::Node::GetNodeInfo()
{
  NodeInfo info;
  info.position[0] = m_x;
  info.position[1] = m_y;
  info.uuid = m_uuid;
  info.nodeId = m_id;
  info.inputConnections.resize(m_elements.size());
  info.elementData = "";
  for (int i = 0; i < m_elements.size(); i++)
  {
    info.inputConnections[i] = m_elements[i]->GetConnectedOutputs();
    info.elementData += " " + m_elements[i]->ExportElementData();
  }
  return info;
}

TextureGenEngine::Canvas2D *TextureGenEngine::Node::GetCanvas()
{
  return dynamic_cast<Canvas2D *>(m_parent);
}

void TextureGenEngine::Node::SetTitle(std::string title)
{
  m_title->SetText(title);
}