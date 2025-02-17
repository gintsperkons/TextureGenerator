#include "DropDown.h"
#include "Clickable.h"
#include "Core/Logger/Logger.h"
#include "Core/Renderer/Text.h"
#include "GUI/GUIManager.h"
#include "Core/Window/Window.h"
#include "Core/Renderer/Mesh.h"
#include "Core/World/ObjectFactory.h"
#include "Core/AssetManager/AssetManager.h"
#include "ScrollView.h"

TextureGenEngine::Dropdown::Dropdown()
    : Component(0, 0, 50, 20)
{
  m_textMesh = new Text();
  m_backgroundColor = Color(0.1f, 0.1f, 0.1f, 1.0f);
  m_dropArrowDown = ObjectFactory::CreateSquare(15, 15, 0.0f, 0.0f, 1.0f, 1.0f);
  m_dropArrowDown->ChangeTexture(TextureGenEngine::LoadTexture("arrowDown.png"));
  m_dropArrowDown->ChangeShader("maskedColor");
  m_dropArrowDown->ChangeColor(1.0f, 1.0f, 1.0f, 1.0f);
  m_dropArrowUp = ObjectFactory::CreateSquare(15, 15, 1.0f, 1.0f, 0.0f, 0.0f);
  m_dropArrowUp->ChangeTexture(TextureGenEngine::LoadTexture("arrowDown.png"));
  m_dropArrowUp->ChangeShader("maskedColor");
  m_dropArrowUp->ChangeColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void TextureGenEngine::Dropdown::Init(float width, float height)
{
  Component::Init(width, height);
  m_width = m_parent->GetWidth();
  m_background->SetSize(m_width, m_height);
  for (auto &element : m_elements)
  {
    element->Init(m_width, m_height);
  }
  m_dropArrowUp->SetPosition(m_x + m_width - 20, m_y + m_titleHeight / 2 - 7.5f);
  m_dropArrowDown->SetPosition(m_x + m_width - 20, m_y + m_titleHeight / 2 - 7.5f);
}

void TextureGenEngine::Dropdown::OnHover(float x, float y)
{

  LOG_DEBUG("HoveringClickable\n");
  if (CheckCollision(x, y))
  {
    LOG_DEBUG("HoveringClickablTRUEe\n");
    LOG_DEBUG("BB %f %f %f %f\n", m_x, m_y, m_width, m_height);
    m_manager->SetCursor(TextureGenEngine::Cursor::PointingHand);
  }
  for (auto &element : m_elements)
  {
    element->OnHover(x, y);
  }
}

void TextureGenEngine::Dropdown::Click(float x, float y)
{
  LOG_DEBUG("Clicking %f %f\n", x, y);
  LOG_DEBUG("BB %f %f %f %f\n", m_x, m_y, m_width, m_titleHeight);
  LOG_DEBUG("test1 m_x < x %d\n", m_x < x);
  LOG_DEBUG("test2 m_x + m_width > x %d\n", m_x + m_width > x);
  LOG_DEBUG("test3 m_y < y %d\n", m_y < y);
  LOG_DEBUG("test4 m_y + m_titleHeight > y %d\n", m_y + m_titleHeight > y);
  bool test = m_x < x && m_x + m_width > x && m_y < y && m_y + m_titleHeight > y;
  LOG_DEBUG("testTOTAL %d\n", test);
  if (m_x < x && m_x + m_width > x && m_y < y && m_y + m_titleHeight > y)
  {
    LOG_DEBUG("ClickingDropdown %d\n", m_opened);
    m_opened = !m_opened;
    if (m_opened)
    {
      float newHeight = m_titleHeight;
      newHeight += 5;
      for (auto &element : m_elements)
      {
        element->SetPosition(m_x, m_y - newHeight);
        newHeight += element->GetHeight();
        newHeight += 5;
      }

      m_height = newHeight;
    }
    if (!m_opened)
    {
      float newHeight = m_titleHeight;
      for (auto &element : m_elements)
      {
        element->SetPosition(m_x, m_y);
      }
      m_height = m_titleHeight;
    }
    if (dynamic_cast<ScrollView *>(m_parent) != nullptr)
    {
      static_cast<ScrollView *>(m_parent)->RecalculateMaxScroll();
    }
    return;
  }
  LOG_DEBUG("ClickingClickable\n");
  for (auto &element : m_elements)
  {
    if (element->CheckCollision(x, y))
    {
      element->Click(x, y);
    }
  }
}

void TextureGenEngine::Dropdown::Move(float x, float y)
{
  Component::Move(x, y);
  for (auto &element : m_elements)
  {
    element->Move(x, y);
  }
  m_dropArrowUp->Move(x, y);
  m_dropArrowDown->Move(x, y);
}

bool TextureGenEngine::Dropdown::CheckCollision(float x, float y)
{
  float x1 = m_x;
  float x2 = m_x + m_width;
  float y1 = m_y + m_titleHeight - m_height;
  float y2 = m_y + m_titleHeight;
  float testX = x;
  float testY = y;
  return testX > x1 && testX < x2 && testY > y1 && testY < y2;
}

void TextureGenEngine::Dropdown::SetText(std::string text)
{
  m_text = text;
}

void TextureGenEngine::Dropdown::SetPosition(float x, float y)
{

  m_x = x;
  m_y = y + m_height - m_titleHeight;
  m_background->SetPosition(m_x, m_y);
  m_dropArrowDown->SetPosition(m_x + m_width - 20, m_y + m_titleHeight / 2 - 7.5f);
  m_dropArrowUp->SetPosition(m_x + m_width - 20, m_y + m_titleHeight / 2 - 7.5f);

  if (m_opened)
  {
    float newHeight = m_titleHeight;
    newHeight += 5;
    for (auto &element : m_elements)
    {
      element->SetPosition(m_x, m_y - newHeight);
      newHeight += element->GetHeight();
      newHeight += 5;
    }
    m_height = newHeight;
  }
}

void TextureGenEngine::Dropdown::AddElement(Component *element)
{
  element->SetParent(this);
  element->SetManager(m_manager);
  m_elements.push_back(element);
}

TextureGenEngine::Dropdown::~Dropdown()
{
}

void TextureGenEngine::Dropdown::Draw()
{
  Component::Draw();
  m_textMesh->Draw(m_text, m_x + 5, m_y, m_titleHeight, m_width, 12, TextureGenEngine::AlignmentHorizontal::LEFT, TextureGenEngine::AlignmentVertical::CENTER);
  if (m_opened)
  {
    for (auto &element : m_elements)
    {
      element->Draw();
    }
  }
  if (m_opened)
  {
    m_dropArrowUp->Draw();
  }
  else
  {
    m_dropArrowDown->Draw();
  }
}
