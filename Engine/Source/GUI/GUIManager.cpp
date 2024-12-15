#include "GUIManager.h"
#include "Components/Component.h"
#include "Core/Logger/Logger.h"
#include "Core/Input/InputEvents.h"
#include "Core/Window/Window.h"
#include "Core/Input/Input.h"
#include "Components/TextInput.h"

void TextureGenEngine::GUIManager::SelectObject(double x, double y)
{
    for (auto &child : m_children)
    {
        if (child->CheckCollision(x, y))
        {
            Component *element = child->SelectObject(x, y);
            if (element)
            {
                currentObject = element;
                currentObject->Select();
                return;
            }
            if (child->IsSelectable())
            {
                currentObject = child;
                currentObject->Select();
                return;
            }
        }
    }
    if (currentObject)
    {
        currentObject->DeSelect();
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
    if (currentObject ) LOG_DEBUG("selected object %s\n", currentObject->GetType().c_str());
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

bool TextureGenEngine::GUIManager::IsSelected(Component *component)
{
    return component == currentObject;
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

void TextureGenEngine::GUIManager::Scissors(int x, int y, int width, int height)
{
    m_window->Scissors(x, y, width, height);
}

void TextureGenEngine::GUIManager::MouseMove(MouseMoveEvent e)
{

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
        SelectObject(e.x, e.y);
        for (auto &child : m_children)
        {
            if (child->CheckCollision(e.x, e.y))
            {
                child->Click(e.x, e.y);
            }
            // child->OnMouseClick(button, action);
        }
    }
    if (e.button == Mouse::ButtonLeft && !e.down)
    {

        LOG_DEBUG("Mouse button released\n");
    }
}

void TextureGenEngine::GUIManager::CharEventAction(CharEvent e)
{

    if (currentObject && currentObject->GetType() == "TextInput")
    {
        ((TextInput *)currentObject)->AddChar(e.codepoint);
    }
}

void TextureGenEngine::GUIManager::KeyAction(int key, int scancode, int action, int mods)
{
    if (action == Key::KeyAction::Press || action == Key::KeyAction::Repeat)
    {
        if (currentObject && currentObject->GetType() == "TextInput")
        {

            if (key == Key::Left)
            {
                ((TextInput *)currentObject)->MoveCursorLeft();
            }
            if (key == Key::Right)
            {
                ((TextInput *)currentObject)->MoveCursorRight();
            }
            if (key == Key::Backspace)
            {
                ((TextInput *)currentObject)->RemoveCharBefore();
            }
            if (key == Key::Delete)
            {
                ((TextInput *)currentObject)->RemoveCharAfter();
            }
        }
    }
}

void TextureGenEngine::GUIManager::ScissorsReset()
{
    m_window->ScissorsReset();
}
