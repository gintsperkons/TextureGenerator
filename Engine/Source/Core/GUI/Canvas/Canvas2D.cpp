#include "Canvas2D.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Logger/Logger.h"

TextureGenEngine::Canvas2D::Canvas2D(int x, int y, int width, int height)
    : BaseElement(x, y, width, height)
{
    m_resizeUpdateX = true;
    m_alignLeft = true;
    m_resizeUpdateY = false;
    m_draggable = true;
    m_scaleHeight = true;
    m_scaleWidth = true;
    LOG_DEBUG("X: %d Y: %d\n", x, y);
    LOG_DEBUG("Size: %d, %d\n", m_width, m_height);
    m_mesh = ObjectFactory::CreateSquare(width, height);
    m_mesh->SetPosition(x, y); 
    m_mesh->ChangeColor(0.1f, 1.0f, 0.1f, 1.0f);
}

void TextureGenEngine::Canvas2D::Draw()
{
    if (m_mesh != nullptr)
        m_mesh->Draw();
    for (BaseElement *child : m_children)
    {
        if (child != nullptr)
            child->Draw();
    }
}

TextureGenEngine::Canvas2D::~Canvas2D()
{
}
