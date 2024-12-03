#include "Panel.h"
#include "Core/Renderer/Mesh.h"
#include "GUI/GUIManager.h"
#include "Core/Logger/Logger.h"


TextureGenEngine::Panel::Panel(int x, int y, int width, int height, ScalingType xScaling, ScalingType yScaling)
: Component(x,y,width,height), m_scalingTypeX(xScaling), m_scalingTypeY(yScaling)
{
}

void TextureGenEngine::Panel::Init(int width, int height)
{
Component::Init(width, height);
LOG_DEBUG("Panel Init %d %d\n", width, height);
if (width == 0 || height == 0)
{
    return;
}
    Resize(width, height);
}

void TextureGenEngine::Panel::Resize(int width, int height)
{
    float xScale = 1;
    float yScale = 1;
    float oldWidth, oldHeight;
    m_manager->GetOldSize(oldWidth, oldHeight);
    LOG_DEBUG("Old Width: %f Old Height: %f\n", oldWidth, oldHeight);
    float newWidth = m_width * width / oldWidth;
    float newHeight = m_height * height / oldHeight;

    if (m_scalingTypeX == ScalingType::FILL)
    {
        xScale = (width-m_x) / m_width;
        m_width = (width - m_x);
    }
    if (m_scalingTypeY == ScalingType::FILL)
    {
        yScale = (height - 50-m_y) / m_height;
        m_height = (height - 50 - m_y);
    }
    if (m_scalingTypeX == ScalingType::FIXED)
    {
        m_width = width;
    }
    if (m_scalingTypeY == ScalingType::FIXED)
    {
        m_height = m_height;
    }
    if (m_scalingTypeX == ScalingType::DYNAMIC)
    {
        xScale = newWidth / m_width;
        m_width = newWidth;
    }
    if (m_scalingTypeY == ScalingType::DYNAMIC)
    {
        yScale = (newHeight - 50) / m_height;
        m_height = newHeight - 50;
    }
    m_background->Scale(xScale, yScale);
    LOG_DEBUG("Resizing Panel to %f %f\n", m_width, m_height);
}

TextureGenEngine::Panel::~Panel()
{
}
