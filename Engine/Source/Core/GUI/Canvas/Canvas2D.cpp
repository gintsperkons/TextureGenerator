#include "Canvas2D.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Logger/Logger.h"


TextureGenEngine::Canvas2D::Canvas2D(int x, int y, int width, int height)
    : BaseElement(x, y, width, height)
{
    m_resizeUpdateX = true;
    m_alignLeft = true;
    m_draggable = true;
    m_resizeUpdateY = false;
    m_scaleHeight = true;
    m_scaleWidth = true;
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

void TextureGenEngine::Canvas2D::Drag(double x, double y)
{
    for (BaseElement *child : m_children)
    {
        child->UpdatePositionByMouseDelta(x, y);
    }
}



void TextureGenEngine::Canvas2D::AddElement(BaseElement *element)
{
    element->UpdatePositionRelativeToParent(m_x, m_y);
    AddChild(element);
}

TextureGenEngine::Canvas2D::~Canvas2D()
{
}
