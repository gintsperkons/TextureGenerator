#include "Mesh.h"
#include <glad/glad.h>
#include <array>
#include "Engine.h"
#include "AABB.h"
#include "Core/Logger/Logger.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Asserts.h"
#include "Core/Renderer/Shaders/Shader.h"
#include "glm/gtc/type_ptr.hpp"

TextureGenEngine::Mesh::Mesh(Vertex2D vertices[], unsigned int vertexCount, unsigned int indices[], unsigned int indexCount)
    : m_indexCount(indexCount)
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

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)offsetof(Vertex2D, Position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)offsetof(Vertex2D, Color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)offsetof(Vertex2D, TexCoords));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_model = glm::mat4(1.0f);
    m_shader = Engine::Get()->GetRenderer()->GetShader("base");

    m_aabb = new AABB(vertices, vertexCount);
}

void TextureGenEngine::Mesh::Draw()
{
    m_shader->Use();
    if (glGetError() != GL_NO_ERROR)
    {
        LOG_ERROR("Shader use error");
    }

    GLint projectionLoc = glGetUniformLocation(m_shader->GetID(), "projection");
    GLint modelLoc = glGetUniformLocation(m_shader->GetID(), "model");
    THAUMA_ASSERT_MSG(projectionLoc != -1, "Failed to get projection uniform location");
    THAUMA_ASSERT_MSG(modelLoc != -1, "Failed to get model uniform location");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m_model));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(TextureGenEngine::Engine::Get()->GetRenderer()->GetProjectionMatrix()));
    if (glGetError() != GL_NO_ERROR)
    {
        LOG_ERROR("Failed to set projection matrix uniform");
    }

    glBindVertexArray(VAO);
    if (glGetError() != GL_NO_ERROR)
    {
        LOG_ERROR("Failed to bind VAO");
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    if (glGetError() != GL_NO_ERROR)
    {
        LOG_ERROR("Failed to bind EBO");
    }

    glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);
    if (glGetError() != GL_NO_ERROR)
    {
        LOG_ERROR("Failed to draw elements");
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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

void TextureGenEngine::Mesh::Move(float x, float y)
{
    m_model = glm::translate(m_model, glm::vec3(x, -y, 0.0f));
}

void TextureGenEngine::Mesh::Scale(float x, float y)
{
    m_model = glm::scale(m_model, glm::vec3(x, y, 1.0f));
}

TextureGenEngine::Mesh::~Mesh()
{
    delete m_aabb;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
