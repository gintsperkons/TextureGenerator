#include "Node.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Renderer/Mesh.h"
#include "Core/Logger/Logger.h"

int nodeWidth = 100;
int nodeTitleHeight = 25;
int nodeBackgroundHeight = 100;

TextureGenEngine::Node::Node(int x, int y):
    BaseElement(x, y, 100,25)
{
    m_resizeUpdateX = true;
    m_alignLeft = true;
    m_resizeUpdateY = false;
    m_draggable = true;
    m_scaleHeight = false;
    m_scaleWidth = false;
    m_mesh = ObjectFactory::CreateSquare(nodeWidth, nodeTitleHeight);
    m_mesh->SetPosition(x, y);
    m_mesh->ChangeColor(0.15f, 0.15f, 0.15f, 1.0f);
    m_background = ObjectFactory::CreateSquare(nodeWidth, nodeBackgroundHeight);
    m_background->SetPosition(x + 2*nodeWidth, y - nodeBackgroundHeight); // TODO make backdround height dynamic
    m_background->ChangeColor(0.25f, 0.25f, 0.25f, 1.0f);
}

void TextureGenEngine::Node::Draw()
{
    m_mesh->Draw();
    m_background->Draw();
}

void TextureGenEngine::Node::UpdatePositionByMouseDelta(double x, double y)
{
    BaseElement::UpdatePositionByMouseDelta(x, y);
    m_background->SetPosition(m_x, m_y - nodeBackgroundHeight);
}

TextureGenEngine::Node::~Node()
{
}
