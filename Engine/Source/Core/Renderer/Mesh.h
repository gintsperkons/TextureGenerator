#pragma once
#include <vector>
#include "Structures/Vertex2D.h"

namespace TextureGenEngine {
	class AABB;
	class Shader;
	class Mesh
	{
		unsigned int VBO, VAO, EBO;
		std::vector<Vertex2D> m_vertices;
		std::vector<unsigned int> m_indices;
		AABB* m_aabb;
		Shader *m_shader;
		unsigned int m_indexCount;
	public:
		Mesh(Vertex2D vertices[], unsigned int vertexCount, unsigned int indices[], unsigned int indexCount);
		void Draw();
		void CheckClickColision(float x, float y);
		~Mesh();
	};
}
