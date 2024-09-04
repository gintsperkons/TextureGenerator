#pragma once
namespace TextureGenEngine {
	class Shader;
	class Mesh
	{
		unsigned int VBO, VAO;
		Shader* m_shader;
	public:
		Mesh();
		void Draw();
		~Mesh();
	};
}
