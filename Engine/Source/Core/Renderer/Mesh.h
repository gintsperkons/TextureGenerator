#pragma once
#include <vector>
#include <string>
#include "Structures/Vertex3D.h"

namespace TextureGenEngine
{
	class Shader;
	class Mesh
	{
		unsigned int VBO, VAO, EBO;
		std::vector<Vertex3D> m_vertices;
		std::vector<unsigned int> m_indices;
		glm::mat4 m_model;
		Shader *m_shader;
		unsigned int m_indexCount;

	public:
		Mesh(Vertex3D vertices[], unsigned int vertexCount, unsigned int indices[], unsigned int indexCount);
		void Draw();
		bool CheckClickCollision(float x, float y);
		void Move(float x, float y);
		void SetPosition(float x, float y);
		void Scale(float x, float y);
		void ChangeColor(float r, float g, float b, float a);
		void ChangeShader(std::string shaderName);
		void SetDepth(float depth);
		~Mesh();
	};
}
