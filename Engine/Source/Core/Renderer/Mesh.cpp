#include "Mesh.h"
#include <glad/glad.h>
#include <array>
#include "Engine.h"
#include "AABB.h"
#include "Core/Logger/Logger.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Renderer/Shaders/Shader.h"



TextureGenEngine::Mesh::Mesh(Vertex2D vertices[], unsigned int vertexCount, unsigned int indices[], unsigned int indexCount)
:m_indexCount(indexCount) 
{
   m_vertices = std::vector<Vertex2D>(vertices, vertices + vertexCount);
   m_indices = std::vector<unsigned int>(indices, indices + indexCount);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex2D), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, Position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, Color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void*)offsetof(Vertex2D, TexCoords));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_shader = Engine::Get()->GetRenderer()->GetShader("base");

    m_aabb = new AABB(vertices, vertexCount);

}



void TextureGenEngine::Mesh::Draw()
{
    m_shader->Use();
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
}

void TextureGenEngine::Mesh::CheckClickColision(float x, float y)
{
    if (m_aabb->CheckColision(x, y))
	{
		LOG_INFO("AABB Colision detected\n");

	}
	else
	{
		LOG_INFO("No AABB Colision detected\n");
	}
}

TextureGenEngine::Mesh::~Mesh()
{
    delete m_aabb;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}
