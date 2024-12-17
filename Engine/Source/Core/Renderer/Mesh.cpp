#include "Mesh.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glad/glad.h>
#include <array>
#include "Engine.h"
#include "Core/Window/Window.h"
#include "Core/Logger/Logger.h"
#include "Core/Renderer/Renderer.h"
#include "Core/Asserts.h"
#include "Core/Renderer/Shaders/Shader.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/matrix_decompose.hpp"
#include <limits>

TextureGenEngine::Mesh::Mesh(Vertex3D vertices[], unsigned int vertexCount, unsigned int indices[], unsigned int indexCount)
    : m_indexCount(indexCount)
{
    m_vertices = std::vector<Vertex3D>(vertices, vertices + vertexCount);
    m_indices = std::vector<unsigned int>(indices, indices + indexCount);
    float minX, minY, maxX, maxY;
    minX = minY = 9999.0f;
    maxX = maxY = -9999.0f;
    for (int i = 0; i < vertexCount; i++)
    {
        minX = std::min(minX, vertices[i].Position.x);
        minY = std::min(minY, vertices[i].Position.y);
        maxX = std::max(maxX, vertices[i].Position.x);
        maxY = std::max(maxY, vertices[i].Position.y);
    }
    m_size[0] = maxX - minX;
    m_size[1] = maxY - minY;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex3D), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *)offsetof(Vertex3D, Position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *)offsetof(Vertex3D, Color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *)offsetof(Vertex3D, TexCoords));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    m_model = glm::mat4(1.0f);
    m_shader = Engine::Get()->GetRenderer()->GetShader("base");
}

void TextureGenEngine::Mesh::Draw()
{
    m_shader->Use();
    if (glGetError() != GL_NO_ERROR)
    {
        GLenum error = glGetError();
        LOG_ERROR("Shader use error : %d", error);
    }

    GLint projectionLoc = glGetUniformLocation(m_shader->GetID(), "projection");
    GLint viewLoc = glGetUniformLocation(m_shader->GetID(), "view");
    GLint modelLoc = glGetUniformLocation(m_shader->GetID(), "model");
    GLint timeLoc = glGetUniformLocation(m_shader->GetID(), "time");
    if (timeLoc != -1)
    {
        glUniform1f(timeLoc, Engine::Get()->GetTime());
    }

    THAUMA_ASSERT_MSG(projectionLoc != -1, "Failed to get projection uniform location");
    THAUMA_ASSERT_MSG(viewLoc != -1, "Failed to get view uniform location");
    THAUMA_ASSERT_MSG(modelLoc != -1, "Failed to get model uniform location");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m_model));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(TextureGenEngine::Engine::Get()->GetRenderer()->GetProjectionMatrix()));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(TextureGenEngine::Engine::Get()->GetRenderer()->GetViewMatrix()));
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

glm::vec3 screenToWorld(float screenX, float screenY)
{
    glm::mat4 inverseProjView = glm::inverse(TextureGenEngine::Engine::Get()->GetRenderer()->GetProjectionMatrix() * TextureGenEngine::Engine::Get()->GetRenderer()->GetViewMatrix());
    int windowWidth, windowHeight;
    TextureGenEngine::Engine::Get()->GetMainWindow()->GetFramebufferSize(windowWidth, windowHeight);
    // Convert screen coordinates to normalized device coordinates (NDC)
    float ndcX = (2.0f * screenX) / windowWidth - 1.0f;
    float ndcY = 1.0f - (2.0f * screenY) / windowHeight;

    // Convert to world space by applying the inverse projection-view matrix
    glm::vec4 worldPos = inverseProjView * glm::vec4(ndcX, ndcY, 0.0f, 1.0f); // Assuming click is on the near plane
    return glm::vec3(worldPos);
    return glm::vec3(0.0f);
}

bool TextureGenEngine::Mesh::CheckClickCollision(float x, float y)
{
    glm::vec3 worldPosCords = screenToWorld(x, y);
    x = worldPosCords.x;
    y = worldPosCords.y;

    glm::vec3 minCorner = glm::vec3(FLT_MAX, FLT_MAX, 0.0f);
    glm::vec3 maxCorner = glm::vec3(-FLT_MAX, -FLT_MAX, 0.0f);

    for (const auto &vertex : m_vertices)
    {
        // Transform the vertex position from local space to world space
        glm::vec4 worldPos = m_model * glm::vec4(vertex.Position, 1.0f); // Apply model matrix (translation, rotation, scale)
        glm::vec3 transformedPos = glm::vec3(worldPos);

        // Update the AABB with the new transformed position
        minCorner = glm::min(minCorner, transformedPos);
        maxCorner = glm::max(maxCorner, transformedPos);
    }
    // If the click is within the bounds of the AABB (in world space), return true
    if (x >= minCorner.x && x <= maxCorner.x && y >= minCorner.y && y <= maxCorner.y)
    {
        return true; // Click is inside the AABB
    }

    // If no collision, return false
    return false;
}

void TextureGenEngine::Mesh::Move(float x, float y)
{

    m_model = glm::translate(m_model, glm::vec3(x / m_scales[0], -y / m_scales[1], 0.0f));
}

void TextureGenEngine::Mesh::SetPosition(float x, float y)
{
    glm::vec3 scale, translation, skew;
    glm::quat rotation;
    glm::vec4 perspective;
    glm::decompose(m_model, scale, rotation, translation, skew, perspective);

    translation = glm::vec3(x, y, translation.z);

    m_model = glm::mat4(1.0);
    m_model = glm::translate(m_model, translation);
    m_model *= glm::mat4_cast(rotation);
    m_model = glm::scale(m_model, scale);
}
void TextureGenEngine::Mesh::Scale(float x, float y)
{
    m_scales[0] = x;
    m_scales[1] = y;
    m_model = glm::scale(m_model, glm::vec3(x, y, 1.0f));
}

void TextureGenEngine::Mesh::SetSize(float width, float height)
{
    m_scales[0] = width / m_size[0];
    m_scales[1] = height / m_size[1];
    m_model = glm::scale(m_model, glm::vec3(m_scales[0], m_scales[1], 1.0f));
    m_size[0] = width;
    m_size[1] = height;
}

void TextureGenEngine::Mesh::ChangeColor(float r, float g, float b, float a)
{
    // Iterate through all vertices and update the color
    for (auto &vertex : m_vertices)
    {
        vertex.Color = glm::vec3(r, g, b); // Update color (you can modify this to fit your needs)
    }

    // Re-upload the vertex data to the GPU with the updated color
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(Vertex3D), m_vertices.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    int error = glGetError();
    if (error != GL_NO_ERROR)
    {
        LOG_WARN("Failed to update vertex buffer with new color: %d\n", error);
    }
}

void TextureGenEngine::Mesh::ChangeShader(std::string shaderName)
{
    m_shader = Engine::Get()->GetRenderer()->GetShader(shaderName);
}

void TextureGenEngine::Mesh::SetDepth(float depth)
{
    glm::vec3 scale, translation, skew;
    glm::quat rotation;
    glm::vec4 perspective;
    glm::decompose(m_model, scale, rotation, translation, skew, perspective);

    translation = glm::vec3(translation.x, translation.y, depth);

    m_model = glm::mat4(1.0);
    m_model = glm::translate(m_model, translation);
    m_model *= glm::mat4_cast(rotation);
    m_model = glm::scale(m_model, scale);

}

TextureGenEngine::Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
