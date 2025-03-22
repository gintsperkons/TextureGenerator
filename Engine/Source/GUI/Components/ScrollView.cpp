#include "ScrollView.h"
#include "Core/Logger/Logger.h"
#include "GUI/GUIManager.h"

TextureGenEngine::ScrollView::ScrollView(float x, float y, float width, float height, ScalingType xScaling, ScalingType yScaling)
    : Panel(x, y, width, height, xScaling, yScaling)
{
    m_draggable = false;
    m_scrollable = true;
    m_selectable = true;
    m_type = "ScrollView";
}

void TextureGenEngine::ScrollView::Init(float width, float height)
{
  Panel::Init(width, height);
  LOG_DEBUG("Deleet %f\n",m_y);
  for (auto &element : m_elements)
  {
    element->Init(m_width, m_height);
  }
}

void TextureGenEngine::ScrollView::Draw()
{
    m_manager->ScissorsPush(m_x, m_y, m_width, m_height);
    Panel::Draw();
    for (auto &element : m_elements)
    {
        element->Draw();
    }
    m_manager->ScissorsPop();
}

void TextureGenEngine::ScrollView::OnHover(float x, float y)
{
    for (auto &element : m_elements)
    {
        element->OnHover(x, y);
    }
}

void TextureGenEngine::ScrollView::Resize(float width, float height)
{
  LOG_DEBUG("Heigh:%f", m_height);
    Panel::Resize(width, height);
    for (auto &element : m_elements)
    {
        element->SetPosition(m_x, m_y + m_height - GetItemOffset(element) - m_scrollOffset);
    }
    m_scrollOffset = 0;
    m_maxScroll = 0;
    m_minScroll = 0;
    RecalculateMaxScroll();
    
}

void TextureGenEngine::ScrollView::Update()
{
  RecalculateMaxScroll();
}

void TextureGenEngine::ScrollView::RecalculateChildPositions()
{
  for (auto &element : m_elements)
  {
    element->SetPosition(m_x, m_y + m_height - GetItemOffset(element) - m_scrollOffset);
  }
}

void TextureGenEngine::ScrollView::AddElement(Component *element)
{
    element->SetParent(this);
    element->SetManager(m_manager);
    m_elements.push_back(element);
    RecalculateMaxScroll();
}

void TextureGenEngine::ScrollView::RecalculateMaxScroll()
{

    float maxScroll = 0;
    maxScroll = 0;
    for (auto &el : m_elements)
    {
      maxScroll += el->GetHeight();
    }

    if (maxScroll <= m_height)
    {
      m_minScroll = 0;
      m_maxScroll = 0;
      m_scrollOffset = 0;
    };
    if (maxScroll <= m_height) {RecalculateChildPositions(); return;};


    maxScroll -= m_height;
    maxScroll *= m_direction;
    if (maxScroll < 0)
    {
        m_minScroll = maxScroll + m_direction*25;
        m_maxScroll = 0;
        if (m_scrollOffset < m_minScroll) m_scrollOffset = m_minScroll;
        RecalculateChildPositions();
        return;
    }

    m_minScroll = 0;
    m_maxScroll = maxScroll + m_direction * 25;
    if (m_scrollOffset > m_maxScroll) m_scrollOffset = m_maxScroll;
    RecalculateChildPositions();
}

TextureGenEngine::Component *TextureGenEngine::ScrollView::SelectObject(float x, float y)
{
    for (auto &element : m_elements)
    {
        if (element->CheckCollision(x, y))
        {
            element->Click(x, y);
            return element;
        }
    }
    if (CheckCollision(x, y))
    {
        return this;
    }
    return nullptr;
}

float TextureGenEngine::ScrollView::GetItemOffset(Component *el)
{
    float offset = 0;
    for (auto &element : m_elements)
    {
        offset += element->GetHeight() + 5;
        if (element == el)
            return offset;
    }
    return offset;
}



void TextureGenEngine::ScrollView::OnScroll(float x, float y)
{
    float scrollDistance = y * m_scrollSpeed;
    if (m_minScroll == 0 && m_maxScroll == 0) return;
    if (m_scrollOffset + scrollDistance < m_minScroll)
    {
        scrollDistance = m_minScroll - m_scrollOffset;
    }
    else if (m_scrollOffset + scrollDistance > m_maxScroll)
    {
        scrollDistance = m_maxScroll - m_scrollOffset;
    }
    m_scrollOffset += scrollDistance;
    for (auto &element : m_elements)
    {
        element->Move(0, scrollDistance);
    }
}

TextureGenEngine::ScrollView::~ScrollView()
{
    for (auto &element : m_elements)
    {
        delete element;
    }
    m_elements.clear();
}
