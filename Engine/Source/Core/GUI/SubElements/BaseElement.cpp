#include "BaseElement.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Logger/Logger.h"

void TextureGenEngine::BaseElement::AddChild(BaseElement *child)
{
    child->m_parent = this;
    m_children.push_back(child);
}

TextureGenEngine::BaseElement *TextureGenEngine::BaseElement::GetDraggable(int x, int y)
{

    for (BaseElement *child : m_children)
    {
        BaseElement *temp = child->GetDraggable(x, y);
        if (temp != nullptr)
            return temp;
    }
    if (m_mesh->CheckClickCollision(x, y) && m_draggable)
    {
        return this;
    }
    return nullptr;
}

void TextureGenEngine::BaseElement::Drag(double x, double y)
{   float newX = m_x + x;
    float newY = m_y - y;
    float pX, pY;
    int width, height;
    m_parent->GetDimensions(width, height);
    m_parent->GetPosition(pX, pY);
    LOG_DEBUG("Parent X: %f, Parent Y: %f\n", pX, pY);
    LOG_DEBUG("Parent Width: %d, Parent Height: %d\n", width, height);
    LOG_DEBUG("Old X: %f, Old Y: %f\n", m_x, m_y);
    LOG_DEBUG("New X: %f, New Y: %f\n", newX, newY);
    LOG_DEBUG("Width: %f, Height: %f\n", m_width, m_height);

    if (newY < pY)
        y = newY - pY;
    if (newX < pX)
        x = pX - newX;
    LOG_TRACE("Val1: %f, Val2: %f\n", newX + m_width, pX + width - m_width);
    LOG_TRACE("X %f, Y %f\n", x, y);
    LOG_TRACE("Val1: %f,%f,%f\n", (pX + width - m_width) , (newX + m_width),(pX + width - m_width) - (newX + width));
    if (newX + m_width > pX + width-m_width)
        x = (pX + width - m_width)-(newX + m_width);
    LOG_TRACE("X %f, Y %f\n", x, y);
    if (newY + m_height > pY + height)
        y = (newY + m_height)-(pY + height) ;

    UpdatePositionByMouseDelta(x, y);
    //m_mesh->SetPosition(m_x, m_y);
}

void TextureGenEngine::BaseElement::CheckCollision(int x, int y)
{
    if (m_mesh != nullptr && m_canClick)
    {
        if (m_mesh->CheckClickCollision(x, y))
        {
            Click();
        }
    }
    for (BaseElement *child : m_children)
    {
        child->CheckCollision(x, y);
    }
}

void TextureGenEngine::BaseElement::Resize(int width, int height, int oldWidth, int oldHeight)
{
    LOG_DEBUG("Resizing element,width: %d, height: %d, oldWidth: %d, oldHeight: %d\n", width, height, oldWidth, oldHeight);
    LOG_DEBUG("X: %d, Y: %d, Width: %d, Height: %d\n", m_x, m_y, m_width, m_height);

    float xDiff, yDiff;
    if (m_scaleHeight)
        if (m_resizeUpdateY)
            yDiff = (float)(height - (oldHeight - m_height)) / (float)m_height;
        // yDiff = (float)height / (float)oldHeight;
        else
            // yDiff = (((float)height /oldHeight) *m_height) / (float)m_height;
            yDiff = (float)(height - (oldHeight - m_height)) / (float)m_height;
    else
        yDiff = 1.0f;

    if (m_scaleWidth)
        // xDiff = (float)width / (float)oldWidth;
        if (m_resizeUpdateX)
            xDiff = (float)(width - (oldWidth - m_width)) / (float)m_width;
        else
            xDiff = (float)(width - (oldWidth - m_width)) / (float)m_width;
    else
        xDiff = 1.0f;

    LOG_DEBUG("XDiff: %f, YDiff: %f\n", xDiff, yDiff);

    int newX = (int)(((float)m_x / oldWidth) * width);
    int newY = (int)(((float)m_y / oldHeight) * height);

    if (!m_resizeUpdateX)
        newX = m_x;
    else if (m_alignLeft)
        newX = m_x;
    if (!m_resizeUpdateY)
        newY = m_y;
    else if (m_alignTop)
        newY = height - m_height;
    // TODO: Fix this so the x stays in place so side bar is same size
    LOG_DEBUG("New X: %d, New Y: %d\n", newX, newY);
    if (m_mesh != nullptr)
    {
        m_mesh->Move((float)(m_x - newX), (float)(m_y - newY));
        m_mesh->Scale((xDiff), (yDiff));
    }

    m_x = newX;
    m_y = newY;
    m_width = ((float)m_width * xDiff);
    m_height = ((float)m_height * yDiff);

    for (BaseElement *child : m_children)
    {
        if (child != nullptr)
            child->Resize(width, height, oldWidth, oldHeight);
    }
}

void TextureGenEngine::BaseElement::UpdatePositionByMouseDelta(double x, double y)
{

    m_x += x;
    m_y -= y;
    m_mesh->Move(x, y);
}

void TextureGenEngine::BaseElement::UpdatePositionRelativeToParent(int x, int y)
{
    m_x += x;
    m_y += y;

    m_mesh->SetPosition(m_x, m_y);
}
