#pragma once

namespace TextureGenEngine
{
	struct ResizeEvent
	{
		int width;
		int height;
	};

	struct MouseClick
	{
		int x;
		int y;
	};

	struct CharacterEvent
	{
		int codePoint;
		wchar_t character;
	};
}