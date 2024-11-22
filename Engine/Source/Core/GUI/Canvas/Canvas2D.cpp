#include "Canvas2D.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Logger/Logger.h"
#include "Engine.h"
#include "Core/Renderer/Renderer.h"



TextureGenEngine::Canvas2D::Canvas2D(int x, int y, int width, int height)
    : BaseElement(x, y, width, height)
{
    //!
    //TODO fix object colision detection in subelements / views
    m_resizeUpdateX = true;
    m_alignLeft = true;
    m_draggable = true;
    m_resizeUpdateY = false;
    m_scaleHeight = true;
    m_scaleWidth = true;
    m_mesh = ObjectFactory::CreateSquare(width, height);
    m_mesh->SetPosition(0, 0); 
    m_mesh->ChangeColor(0.2f, 0.2f, 0.2f, 1.0f);
}

void TextureGenEngine::Canvas2D::Draw()
{
    TextureGenEngine::Engine::Get()->GetRenderer()->UseCustomViewport(m_x, m_y, m_width, m_height);
    if (m_mesh != nullptr)
        m_mesh->Draw();
    for (BaseElement *child : m_children)
    {
        if (child != nullptr)
            child->Draw();
    }
    TextureGenEngine::Engine::Get()->GetRenderer()->UseDefaultViewport();
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

TextureGenEngine::BaseElement *TextureGenEngine::Canvas2D::GetDraggable(int x, int y)
{
    for (BaseElement *child : m_children)
    {
        BaseElement *temp = child->GetDraggable(x-m_x, y-m_y);
        if (temp != nullptr)
            return temp;
    }
    if (m_mesh->CheckClickCollision(x - m_x, y -m_y) && m_draggable)
    {
        return this;
    }
    return nullptr;
}

TextureGenEngine::Canvas2D::~Canvas2D()
{
}
