#include <GLFW/glfw3.h>
#include "Input.h"
#include "Core/Window/Window.h"
#include "Engine.h"

bool TextureGenEngine::Input::MouseButtonPressed(TextureGenEngine::Mouse::MouseCode button)
{
	auto* window = Engine::Get()->GetWindow()->GetNativeWindow();
	auto state = glfwGetMouseButton(window, static_cast<int>(button));
	if (state == GLFW_PRESS)
		return true;
	return false;
}
