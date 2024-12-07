#include "GUIManager.h"
#include "Components/Component.h"
#include "Core/Logger/Logger.h"
#include "Core/Input/InputEvents.h"
#include "Core/Window/Window.h"
#include "Core/Input/Input.h"

void TextureGenEngine::GUIManager::GetDraggableComponent(double x, double y)
{
    LOG_DEBUG("Getting draggable component\n");
    for (auto &child : m_children)
    {
        LOG_DEBUG("searching found type %s\n", child->GetType().c_str());
        if (child->CheckCollision(x, y))
        {
            Component *element = child->GetDraggableComponent(x, y);
            if (element)
            {
                LOG_DEBUG("Element found type %s\n", element->GetType().c_str());
                currentObject = element;

                return;
            }
        }
    }
    currentObject = nullptr;
}

TextureGenEngine::GUIManager::GUIManager()
{
}

TextureGenEngine::GUIManager::~GUIManager()
{
    for (auto &child : m_children)
    {
        delete child;
    }
    m_children.clear();
}

void TextureGenEngine::GUIManager::Update()
{
    for (int i = 0; i <= Mouse::ButtonLast; i++)
    {
        if (m_mouseButtonStates[i] == Mouse::Pressed)
        {
            m_mouseButtonStates[i] = Mouse::Held;
        }
    }
}

void TextureGenEngine::GUIManager::Draw()
{
    for (auto &child : m_children)
    {
        child->Draw();
    }
}

void TextureGenEngine::GUIManager::AddComponent(Component *component)
{
    component->SetManager(this);
    m_children.push_back(component);
}

void TextureGenEngine::GUIManager::Resize(int width, int height)
{
    m_oldWidth = m_width;
    m_oldHeight = m_height;
    m_width = width;
    m_height = height;
    LOG_DEBUG("Resizing GUIManager to %d %d\n", width, height);
    for (auto &child : m_children)
    {
        child->Resize(width, height);
    }
}

void TextureGenEngine::GUIManager::Init(int width, int height)
{
    m_oldWidth = m_width;
    m_oldHeight = m_height;
    m_width = width;
    m_height = height;
    if (m_oldWidth == 0 && m_oldHeight == 0)
    {
        m_oldWidth = width;
        m_oldHeight = height;
    }
    for (auto &child : m_children)
    {
        child->Init(width, height);
    }
}

void TextureGenEngine::GUIManager::GetOldSize(float &width, float &height)
{
    width = m_oldWidth;
    height = m_oldHeight;
}

void TextureGenEngine::GUIManager:: Scissors(int x, int y, int width, int height)
{
    m_window->Scissors(x, y, width, height);
}

void TextureGenEngine::GUIManager::MouseMove(MouseMoveEvent e)
{
    LOG_DEBUG("Mouse moved x: %f, y: %f\n", e.x, e.y);
    LOG_DEBUG("left button state: %d\n", m_mouseButtonStates[Mouse::ButtonLeft]);
    LOG_DEBUG("current object: %p\n", currentObject);

    if (currentObject && m_mouseButtonStates[Mouse::ButtonLeft] == Mouse::Held)
    {
        currentObject->OnMouseDrag(e.x, e.y);
    }
}

void TextureGenEngine::GUIManager::MouseClick(MouseButtonEvent e)
{
    m_mouseButtonStates[e.button] = e.down ? Mouse::Pressed : Mouse::Released;
    if (e.button == Mouse::ButtonLeft && e.down)
    {
        GetDraggableComponent(e.x, e.y);
        for (auto &child : m_children)
        {
            if (child->CheckCollision(e.x, e.y))
            {
                LOG_DEBUG("Collision detected x: %f, y: %f button: %d down: %d\n", e.x, e.y, e.button, e.down);
                child->Click(e.x, e.y);
            }
            // child->OnMouseClick(button, action);
        }
    }
    if (e.button == Mouse::ButtonLeft && !e.down)
    {
        currentObject = nullptr;
    }
}

void TextureGenEngine::GUIManager::ScissorsReset()
{
    m_window->ScissorsReset();
}
