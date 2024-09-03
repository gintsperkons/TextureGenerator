#include "Input.h"
#include "Window.h"
#include <GLFW/glfw3.h>


void processKeyInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

TextureGenEngine::Input::Input(Window* window)
{
	glfwSetKeyCallback(window->GetWindow(), processKeyInput);
}


TextureGenEngine::Input::~Input()
{
}
