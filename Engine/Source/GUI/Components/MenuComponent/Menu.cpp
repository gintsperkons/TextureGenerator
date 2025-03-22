#include "Menu.h"
#include "Core/Renderer/Text.h"
#include "Core/Logger/Logger.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Window/Window.h"
#include "GUI/GUIManager.h"
#include "MenuItem.h"

TextureGenEngine::Menu::Menu(std::string title) : m_title(title),
                                                  MenuComponent(MenuComponent::height)
{
  m_text = new Text();
}

void TextureGenEngine::Menu::Draw()
{
  MenuComponent::Draw();
  m_text->Draw(m_title, m_x, m_y, (int)m_height, (int)m_width, 12, AlignmentHorizontal::LEFT, AlignmentVertical::CENTER);
  if (m_opened)
  {
    for (auto &element : m_menuItems)
    {
      element->Draw();
    }
  }
}

void TextureGenEngine::Menu::Init(float width, float height)
{
  MenuComponent::Init(width, height);
  m_y = height - m_height;
  m_background->SetPosition(m_x, m_y);

  for (auto &element : m_menuItems)
  {
    element->Init(width, height);
  }
}

void TextureGenEngine::Menu::AddItem(MenuItem *item)
{
  item->SetParent(this);
  item->SetManager(m_manager);
  item->SetPosition(m_x, m_y - m_height);
  m_menuItems.push_back(item);
}

void TextureGenEngine::Menu::Click(float x, float y)
{
  LOG_DEBUG("ClickingMenuItemTasdsadest\n");
  if (m_opened)
  {
    for (auto &element : m_menuItems)
    {
      element->Click(x, y);
    }
  }
  if (CheckCollision(x, y))
  {
    m_opened = !m_opened;
  }
}

void TextureGenEngine::Menu::OnHover(float x, float y)
{
  if (CheckCollision(x, y))
  {
    m_manager->SetCursor(Cursor::PointingHand);
  }
}

void TextureGenEngine::Menu::Resize(float width, float height)
{
  m_y = height - m_height;
  m_background->SetPosition(m_x, m_y);
}

void TextureGenEngine::Menu::SetMenuBar(float x, float y, float width, float height)
{
  m_x = x;
  m_y = y;
  m_background->Scale(width / m_width, 1);
  m_width = width;
  m_height = height;
  m_background->SetPosition(m_x, MenuComponent::height);
}

float TextureGenEngine::Menu::GetElementOffset(MenuItem *item)
{
  float offset = 0;
  for (auto &element : m_menuItems)
  {
    if (element == item)
    {
      break;
    }
    offset += element->GetHeight();
  }
  return offset;
}

TextureGenEngine::Menu::~Menu()
{
  delete m_text;
}
