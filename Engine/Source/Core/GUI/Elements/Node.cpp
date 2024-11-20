#include "Node.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Logger/Logger.h"

TextureGenEngine::Node::Node(int x, int y, int width, int height):
    BaseElement(x, y, width, height)
{
    m_resizeUpdateX = true;
    m_alignLeft = true;
    m_resizeUpdateY = false;
    m_draggable = true;
    m_scaleHeight = false;
    m_scaleWidth = false;
    m_mesh = ObjectFactory::CreateSquare(width, height);
    m_mesh->SetPosition(x, y);
    m_mesh->ChangeColor(1.0f, 0.1f, 0.1f, 1.0f);
}

void TextureGenEngine::Node::Draw()
{
    m_mesh->Draw();
}

TextureGenEngine::Node::~Node()
{
}
