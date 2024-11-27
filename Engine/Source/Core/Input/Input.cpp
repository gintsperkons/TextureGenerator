#include <GLFW/glfw3.h>
#include "Input.h"
#include "Core/Window/Window.h"
#include "Engine.h"
#include "Core/Logger/Logger.h"

int TextureGenEngine::Input::g_mouseButtonStates[TextureGenEngine::Mouse::ButtonLast + 1] = {0};
int TextureGenEngine::Input::g_keyStates[1024] = {0};
std::vector<int> TextureGenEngine::Input::g_pressedKeys = {};
double TextureGenEngine::Input::g_mouseDelta[2] = {0};
double TextureGenEngine::Input::g_mousePos[2] = {0};


bool TextureGenEngine::Input::MouseButtonPressed(TextureGenEngine::Mouse::MouseCode button)
{
	if (g_mouseButtonStates[button] == TextureGenEngine::Mouse::Pressed)
	{
		return true;
	}
	return false;
}

bool TextureGenEngine::Input::MouseButtonHeld(TextureGenEngine::Mouse::MouseCode button)
{
	if (g_mouseButtonStates[button] == TextureGenEngine::Mouse::Held)
	{
		return true;
	}
	return false;
}

bool TextureGenEngine::Input::MouseButtonReleased(TextureGenEngine::Mouse::MouseCode button)
{
	if (g_mouseButtonStates[button] == TextureGenEngine::Mouse::Released)
	{
		return true;
	}
	return false;
}

TAPI bool TextureGenEngine::Input::KeyPressed(int key)
{
	if (key == Key::KeyAny)
	{
		if (g_pressedKeys.size() > 0)
		{
			return true;
		}
		return false;
	}
	if (g_keyStates[key] == 1)
	{
		return true;
	}
	return false;
}

TAPI std::vector<int> TextureGenEngine::Input::GetPressedKeys()
{
	return g_pressedKeys;
}

int *TextureGenEngine::Input::GetMousePosition()
{
	static int pos[2];
	double x, y;
	glfwGetCursorPos(TextureGenEngine::Engine::Get()->GetWindow()->GetNativeWindow(), &x, &y);
	pos[0] = (int)x;
	pos[1] = (int)y;
	return pos;
}

double *TextureGenEngine::Input::GetMouseDelta()
{
	return g_mouseDelta;
}
