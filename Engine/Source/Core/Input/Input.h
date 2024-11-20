#pragma once
#include "Defines.h"
#include "MouseCodes.h"



namespace TextureGenEngine
{
	namespace Input
	{	extern double g_mouseDelta[2];
		extern double g_mousePos[2];
		extern int g_mouseButtonStates[Mouse::ButtonLast+1];
		TAPI bool MouseButtonPressed(TextureGenEngine::Mouse::MouseCode button);
		TAPI bool MouseButtonHeld(TextureGenEngine::Mouse::MouseCode button);
		TAPI bool MouseButtonReleased(TextureGenEngine::Mouse::MouseCode button);
		TAPI int* GetMousePosition();
		TAPI double* GetMouseDelta();
	};
}
