#pragma once

namespace TextureGenEngine {
	class AABB;
	class Shader;
	class Mesh
	{
		unsigned int VBO, VAO, EBO;
		AABB* m_aabb;
		Shader* m_shader;
		unsigned int m_indexCount;
	public:
		Mesh(float vertices[], unsigned int vertexCount, unsigned int indices[], unsigned int indexCount);
		void Draw();
		void CheckClickColision(float x, float y);
		~Mesh();
	};
}
