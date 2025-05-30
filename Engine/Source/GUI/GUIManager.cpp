#include "GUIManager.h"
#include "Components/Component.h"
#include "Core/Logger/Logger.h"
#include "Core/Input/InputEvents.h"
#include "Core/Window/Window.h"
#include "Core/Input/Input.h"
#include "Components/TextInput.h"

void TextureGenEngine::GUIManager::SelectObject(float x, float y)
{
    for (auto &child : m_children)
    {
        if (currentObject)
        {
            currentObject->DeSelect();
        }
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

    currentObject = nullptr;
}

TextureGenEngine::GUIManager::GUIManager() : m_oldHeight(0), m_oldWidth(0), m_width(0), m_height(0)
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
    if (m_width <= 0 || m_height <= 0)
        return;

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

void TextureGenEngine::GUIManager::Resize(float width, float height)
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

void TextureGenEngine::GUIManager::Init(float width, float height)
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

void TextureGenEngine::GUIManager::MouseMove(MouseMoveEvent e)
{

    if (currentObject && m_mouseButtonStates[Mouse::ButtonLeft] == Mouse::Held)
    {
        currentObject->OnMouseDrag((float)e.x, (float)e.y);
        return;
    }
    double x, y;
    m_window->GetInput()->GetMousePosition(x, y);
    m_cursorChanged = false;
    for (auto &child : m_children)
    {
        if (child->CheckCollision((float)x, (float)y))
        {
            child->OnHover((float)x, (float)y);
        }
    }
    if (!m_cursorChanged)
    {
        m_window->SetCursor(Cursor::Arrow);
    }
}

void TextureGenEngine::GUIManager::MouseClick(MouseButtonEvent e)
{
    m_mouseButtonStates[e.button] = e.down ? Mouse::Pressed : Mouse::Released;
    if (e.button == Mouse::ButtonLeft && e.down)
    {
        SelectObject((float)e.x, (float)e.y);
        for (auto &child : m_children)
        {
            
                child->Click((float)e.x, (float)e.y);
            
            // child->OnMouseClick(button, action);
        }
    }
    if (e.button == Mouse::ButtonLeft && !e.down)
    {
        if (currentObject)
        {
            currentObject->MouseRelease();
        }
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
        if (currentObject && currentObject->GetType() == "Node")
        {
            if (key == Key::Delete)
            {
                delete currentObject;
                currentObject = nullptr;
                return;
            }
        }
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

void TextureGenEngine::GUIManager::ScissorsPush(float x, float y, float width, float height)
{
    if (m_scissors.size() > 0)
    {
        if (x < m_scissors.back().x)
        {
            x = m_scissors.back().x;
            width = width - (m_scissors.back().x - x);
        }
        if (y < m_scissors.back().y)
        {
            y = m_scissors.back().y;
            height = height - (m_scissors.back().y - y);
        }
    }
    m_scissors.push_back(ScissorsData(x, y, width, height));
    m_window->Scissors(x, y, width, height);
}

void TextureGenEngine::GUIManager::ScissorsPop()
{
    if (m_scissors.size() == 0)
    {
        return;
    }
    m_scissors.pop_back();
    if (m_scissors.size() > 0)
    {
        m_window->Scissors(m_scissors.back().x, m_scissors.back().y, m_scissors.back().width, m_scissors.back().height);
    }
    else
    {
        m_window->ScissorsReset();
    }
}

void TextureGenEngine::GUIManager::GetMousePosition(float &x, float &y)
{
    double xpos, ypos;
    m_window->GetInput()->GetMousePosition(xpos, ypos);
    x = (float)xpos;
    y = (float)ypos;
}

void TextureGenEngine::GUIManager::SetCursor(Cursor cursor)
{
    m_cursorChanged = true;
    m_window->SetCursor(cursor);
    if (m_cursor == (int)cursor)
        return;
    m_cursor = (int)cursor;
}

void TextureGenEngine::GUIManager::Scroll(float x, float y)
{
    double xpos, ypos;
    m_window->GetInput()->GetMousePosition(xpos, ypos);
    for (auto &child : m_children)
    {
        if(child->IsScrollable() && child->CheckCollision(float(xpos), float(ypos)))
        {
            child->OnScroll(x, y);
        }
    }
}
