#include "Node.h"
#include "Core/Renderer/Mesh.h"
#include "Core/World/ObjectFactory.h"
#include "Core/Logger/Logger.h"
#include "GUI/GUIManager.h"
#include "Core/Window/Window.h"
#include "NodeElements/NodeElement.h"

TextureGenEngine::Node::Node(int x, int y):
Component(x, y, 100, c_titleHeight)
{
    m_dataBackground = ObjectFactory::CreateSquare(100, 100);
    m_draggable = true;
    m_type = "Node";
}

void TextureGenEngine::Node::Init(int width, int height)
{
    if (m_parent)
    {
        m_x = m_parent->GetX() + m_x;
        m_y = m_parent->GetY() + m_y;
        m_dataBackground->SetPosition(m_x, m_y-100);
    }
    Component::Init(width, height);
}

void TextureGenEngine::Node::Draw()
{
    Component::Draw();
    m_dataBackground->Draw();
}

void TextureGenEngine::Node::AddElement(NodeElement *element)
{
    m_elements.push_back(element);
    element->AddParentNode(this);
    element->Setup();
}

void TextureGenEngine::Node::OnMouseDrag(double x, double y)
{
    Component::OnMouseDrag(x, y);
    m_dataBackground->Move(x, y);
}

bool TextureGenEngine::Node::CheckCollision(float x, float y)
{
    float x1 = m_x;
    float x2 = m_x + m_width;
    float y1 = m_y;
    float y2 = m_y + m_height;
    float testX = x;
    float testY = y;


float oldWidth, oldHeight;
m_manager->GetOldSize(oldWidth, oldHeight);

    if (testX > x1 && testX < x2 && testY > y1 && testY < y2)
    {
        return true;
    }
    return false;
}

TextureGenEngine::Node::~Node()
{
}
