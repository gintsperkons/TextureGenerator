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
    LOG_DEBUG("Hovering\n");
    for (auto &element : m_elements)
    {
        element->OnHover(x, y);
    }
}

void TextureGenEngine::ScrollView::Resize(float width, float height)
{
    Panel::Resize(width, height);
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
    maxScroll -= m_height;
    maxScroll *= m_direction;
    if (maxScroll < 0)
    {
        m_minScroll = maxScroll;
        m_maxScroll = 0;
        return;
    }

    m_minScroll = 0;
    m_maxScroll = maxScroll;
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
    if (m_scrollOffset + scrollDistance < m_minScroll)
    {
        scrollDistance = m_minScroll - m_scrollOffset;
    }
    if (m_scrollOffset + scrollDistance > m_maxScroll)
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
