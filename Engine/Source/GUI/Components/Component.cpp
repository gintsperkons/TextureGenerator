#include "Component.h"
#include "Core/Renderer/Mesh.h"
#include "Core/World/ObjectFactory.h"
#include "GUI/GUIManager.h"
#include "Core/Logger/Logger.h"

TextureGenEngine::Component::Component(float x, float y, float width, float height) : m_x(static_cast<float>(x)), m_y(static_cast<float>(y)), m_width(static_cast<float>(width)), m_height(static_cast<float>(height))
{
    LOG_DEBUG("Width %f\n", m_width);
    m_background = ObjectFactory::CreateSquare(width, height);
}

void TextureGenEngine::Component::Draw()
{
    if (m_background)
    {
        m_background->Draw();
    }
}

TextureGenEngine::Component::~Component()
{
    if (m_background)
        delete m_background;
}

void TextureGenEngine::Component::Resize(float width, float height)
{

    float oldWidth, oldHeight;
    m_manager->GetOldSize(oldWidth, oldHeight);
    float newWidth = m_width * width / oldWidth;
    float newHeight = m_height * height / oldHeight;
    m_background->Scale(newWidth / m_width, newHeight / m_height);
    m_width = newWidth;
    m_height = newHeight;
}

void TextureGenEngine::Component::SetBackground(Color color)
{
    m_backgroundColor = color;
    m_background->ChangeColor(color.r, color.g, color.b, color.a);
}

void TextureGenEngine::Component::Init(float width, float height)
{
    m_background->SetPosition(m_x, m_y);
    m_background->ChangeColor(m_backgroundColor.r, m_backgroundColor.g, m_backgroundColor.b, m_backgroundColor.a);
}

bool TextureGenEngine::Component::CheckCollision(float x, float y)
{
    float x1 = m_x;
    float x2 = m_x + m_width;
    float y1 = m_y;
    float y2 = m_y + m_height;
    float testX = x;
    float testY = y;

    LOG_DEBUG("x1: %f, x2: %f, y1: %f, y2: %f\n", x1, x2, y1, y2);
    LOG_DEBUG("testX: %f, testY: %f\n", testX, testY);
    if (testX > x1 && testX < x2 && testY > y1 && testY < y2)
    {
        return true;
    }
    return false;
}

void TextureGenEngine::Component::OnMouseDrag(float x, float y)
{
    LOG_DEBUG("Dragging\n");
    if (m_draggable)
    {
        m_x += x;
        m_y -= y;

        m_background->Move(x, y);
    }
}

void TextureGenEngine::Component::SetDepth(float depth)
{
    m_background->SetDepth(depth);
}

void TextureGenEngine::Component::SetPosition(float x, float y)
{

    m_x = x;
    m_y = y;
    m_background->SetPosition(x, y);
}

void TextureGenEngine::Component::Move(float x, float y)
{
    m_x += x;
    m_y -= y;
    m_background->Move(x, y);
}
