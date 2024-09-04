#pragma once

namespace TextureGenEngine
{
	class Shader
	{
		unsigned int ID;
	public:
		Shader();
		void Use();
		~Shader();
	};
}
