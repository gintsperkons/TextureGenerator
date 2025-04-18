#include "Panel.h"
#include "Core/Renderer/Mesh.h"
#include "GUI/GUIManager.h"
#include "Core/Logger/Logger.h"
#include "GUI/Components/MenuComponent/MenuComponent.h"


TextureGenEngine::Panel::Panel(float x, float y, float width, float height, ScalingType xScaling, ScalingType yScaling)
: Component(x,y,width,height), m_scalingTypeX(xScaling), m_scalingTypeY(yScaling)
{
}

void TextureGenEngine::Panel::Init(float width, float height)
{
Component::Init(width, height);
LOG_DEBUG("Panel Init %d %d\n", width, height);
if (width == 0 || height == 0)
{
    return;
}
    Resize(width, height);
}

void TextureGenEngine::Panel::Resize(float width, float height)
{
    float xScale = 1;
    float yScale = 1;
    float oldWidth, oldHeight;
    m_manager->GetOldSize(oldWidth, oldHeight);
    float newWidth = m_width * width / oldWidth;
    float newHeight = m_height * height / oldHeight;

    if (m_scalingTypeX == ScalingType::FILL)
    {
        xScale = (width-m_x) / m_width;
        m_width*=xScale;
    }
    if (m_scalingTypeY == ScalingType::FILL)
    {
        yScale = (height - MenuComponent::height-m_y) / m_height;
        m_height *= yScale;
    }
    if (m_scalingTypeX == ScalingType::FIXED)
    {
        m_width = m_width;
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
      yScale = (m_manager->GetHeight() - MenuComponent::height) / m_height;
      m_height = m_manager->GetHeight() - MenuComponent::height;
    }
    LOG_DEBUG("Heigh:%f", m_height);

    m_background->Scale(xScale, yScale);
}



TextureGenEngine::Panel::~Panel()
{
}
