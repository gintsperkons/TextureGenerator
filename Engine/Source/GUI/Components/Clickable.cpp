#include "Clickable.h"
#include "Core/Renderer/Text.h"
#include "Core/Logger/Logger.h"
#include "ScrollView.h"

TextureGenEngine::Clickable::Clickable()
: Component(0,20,0,0)
{
    m_text = "Clickable text here";
    m_textMesh = new Text();
    m_height = 20;
}

void TextureGenEngine::Clickable::Draw()
{
    Component::Draw();
    m_textMesh->Draw(m_text, m_x+5, m_y, m_height, m_width, 12, TextureGenEngine::AlignmentHorizontal::LEFT, TextureGenEngine::AlignmentVertical::CENTER);
}

void TextureGenEngine::Clickable::Init(float width, float height)
{
    Component::Init(width, height);
    if (!m_parent){
        LOG_DEBUG("Parent is null\n");
    }
    if (m_parent)
    {
        m_width = m_parent->GetWidth();
        m_x = m_parent->GetX();
        m_y = m_parent->GetY() + m_parent->GetHeight() - static_cast<ScrollView*>(m_parent)->GetItemOffset(this);
    }

}

TextureGenEngine::Clickable::~Clickable()
{
}

void TextureGenEngine::Clickable::Click(float x, float y)
{
    if (m_onClick)
    {
        m_onClick();
    }
}

void TextureGenEngine::Clickable::OnClick(std::function<void()> onClick)
{
    LOG_DEBUG("Setting on click\n");
    m_onClick = onClick;
}
