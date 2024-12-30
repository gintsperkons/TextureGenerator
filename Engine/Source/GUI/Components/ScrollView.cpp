#include "ScrollView.h"

TextureGenEngine::ScrollView::ScrollView(float x, float y, float width, float height, ScalingType xScaling, ScalingType yScaling)
    : Panel(x, y, width, height, xScaling, yScaling)
{
    m_draggable = true;
    m_selectable = true;
    m_type = "ScrollView";
}

void TextureGenEngine::ScrollView::Init(float width, float height)
{
    Panel::Init(width, height);
    for (auto &element : m_elements)
    {
        element->Init(width, height);
    }
}

void TextureGenEngine::ScrollView::Draw()
{
    Panel::Draw();
    for (auto &element : m_elements)
    {
        element->Draw();
    }
}

void TextureGenEngine::ScrollView::AddElement(Component *element)
{
    element->SetParent(this);
    m_elements.push_back(element);
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

TextureGenEngine::ScrollView::~ScrollView()
{
    for (auto &element : m_elements)
    {
        delete element;
    }
    m_elements.clear();
}
