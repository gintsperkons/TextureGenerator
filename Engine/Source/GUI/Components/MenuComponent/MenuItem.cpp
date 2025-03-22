#include "MenuItem.h"
#include "Core/Logger/Logger.h"
#include "Menu.h"
#include "Core/Renderer/Text.h"
#include "Core/Renderer/Mesh.h"

TextureGenEngine::MenuItem::MenuItem(std::string text, std::function<void()> onClick) : MenuComponent(MenuItem::height), m_textMesh(new Text()), m_onClick(onClick), m_text(text)
{
  m_backgroundColor = Color(0.3f, 0.3f, 0.3f, 1.0f);
  m_background->ChangeColor(m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a);
}

TextureGenEngine::MenuItem::~MenuItem()
{
}

void TextureGenEngine::MenuItem::Init(float width, float height)
{
  MenuComponent::Init(width, height);
  if (m_parent && dynamic_cast<Menu *>(m_parent))
  {
    float selftOffset = (float)dynamic_cast<Menu *>(m_parent)->GetElementOffset(this);
    LOG_DEBUG("selftOffset: %f\n", selftOffset);
    m_y = m_parent->GetY() - selftOffset - m_parent->GetHeight();
    m_x = m_parent->GetX();
    m_background->SetPosition(m_x, m_y);
    
    m_width = width;
  }
}

void TextureGenEngine::MenuItem::Draw()
{
  Component::Draw();
  m_background->Draw();
  m_textMesh->Draw(m_text, m_x + 5, m_y, (int)m_height, (int)m_width, 12, AlignmentHorizontal::LEFT, AlignmentVertical::CENTER);
}

void TextureGenEngine::MenuItem::Click(float x, float y)
{
  LOG_DEBUG("ClickingMenuItemTest\n");

  if (CheckCollision(x, y))
  {
    m_onClick();
  }
}

void TextureGenEngine::MenuItem::OnHover(float x, float y)
{
}
