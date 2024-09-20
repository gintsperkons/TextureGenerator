#pragma once
#include "Defines.h"
#include "MouseCodes.h"



namespace TextureGenEngine
{
	namespace Input
	{
		extern int g_mouseButtonStates[Mouse::ButtonLast+1];
		TAPI bool MouseButtonPressed(TextureGenEngine::Mouse::MouseCode button);
		TAPI bool MouseButtonHeld(TextureGenEngine::Mouse::MouseCode button);
		TAPI int* GetMousePosition();
	};
}
