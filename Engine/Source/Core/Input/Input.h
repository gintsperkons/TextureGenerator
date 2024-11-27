#pragma once
#include <vector>
#include "Defines.h"
#include "MouseCodes.h"
#include "KeyCodes.h"	



namespace TextureGenEngine
{
	namespace Input
	{	extern double g_mouseDelta[2];
		extern double g_mousePos[2];
		extern int g_mouseButtonStates[Mouse::ButtonLast+1];
		extern int g_keyStates[1024];
		extern std::vector<int> g_pressedKeys;
		TAPI bool MouseButtonPressed(TextureGenEngine::Mouse::MouseCode button);
		TAPI bool MouseButtonHeld(TextureGenEngine::Mouse::MouseCode button);
		TAPI bool MouseButtonReleased(TextureGenEngine::Mouse::MouseCode button);
		TAPI bool KeyPressed(int key);
		TAPI std::vector<int> GetPressedKeys();
		TAPI int* GetMousePosition();
		TAPI double* GetMouseDelta();
	};
}
