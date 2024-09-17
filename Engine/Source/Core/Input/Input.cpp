#include <GLFW/glfw3.h>
#include "Input.h"
#include "Core/Window/Window.h"
#include "Engine.h"
#include "Core/Logger/Logger.h"

int TextureGenEngine::Input::g_mouseButtonStates[TextureGenEngine::Mouse::ButtonLast+1] = {0};

bool TextureGenEngine::Input::MouseButtonPressed(TextureGenEngine::Mouse::MouseCode button)
{
	if (g_mouseButtonStates[button] == TextureGenEngine::Mouse::Pressed)
	{
		return true;
	}
	return false;
}
