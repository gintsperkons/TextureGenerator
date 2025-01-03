#include "Line.h"
#include <glad/glad.h>
#include "Core/Logger/Logger.h"
#include "Core/Renderer/Shaders/Shader.h"
#include "Core/Asserts.h"
#include "Engine.h"
#include "Core/Renderer/Renderer.h"
#include <glm/gtc/type_ptr.hpp>

TextureGenEngine::Line::Line(Vertex3D start, Vertex3D end)
    : m_shader(nullptr), m_indexCount(2)
{
    // Initialize vertices with start and end points
    m_vertices.push_back(start);
    m_vertices.push_back(end);
    m_shader = TextureGenEngine::Engine::Get()->GetRenderer()->GetShader("base");
    // Define indices for the line (2 vertices make 1 line)
    m_indices = {0, 1};

    // Default model matrix is identity
    m_model = glm::mat4(1.0f);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Vertex buffer setup
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex3D), &m_vertices[0], GL_STATIC_DRAW);

    // Element buffer setup
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

    // Vertex attribute pointer for position (location = 0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *)offsetof(Vertex3D, Position));
    glEnableVertexAttribArray(0);

    // Vertex attribute pointer for color (location = 1)
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *)offsetof(Vertex3D, Color));
    glEnableVertexAttribArray(1);

    // Vertex attribute pointer for texCoords (location = 2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *)offsetof(Vertex3D, TexCoords));
    glEnableVertexAttribArray(2);
    glLineWidth(5.0f); // Set line width to 3 pixels (can adjust as needed)

    // Unbind VAO to avoid unintended modifications
    glBindVertexArray(0);
}

TextureGenEngine::Line::~Line()
{
    if (VAO != 0)
        glDeleteVertexArrays(1, &VAO);
    VAO = 0;
    if (VBO != 0)
        glDeleteBuffers(1, &VBO);
    VBO = 0;
    if (EBO != 0)
        glDeleteBuffers(1, &EBO);
    EBO = 0;
}

void TextureGenEngine::Line::Draw()
{
    if (!m_shader)
    {
        LOG_ERROR("Shader is not set. Aborting draw call.");
        return;
    }

    // Use the shader program
    m_shader->Use();

    // Retrieve and set the uniform locations
    GLint projectionLoc = glGetUniformLocation(m_shader->GetID(), "projection");
    GLint modelLoc = glGetUniformLocation(m_shader->GetID(), "model");

    if (projectionLoc == -1)
    {
        LOG_ERROR("Uniform 'projection' not found in shader.");
    }
    else
    {
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(TextureGenEngine::Engine::Get()->GetRenderer()->GetProjectionMatrix()));
    }

    if (modelLoc == -1)
    {
        LOG_ERROR("Uniform 'model' not found in shader.");
    }
    else
    {
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m_model));
    }

    // Initialize OpenGL buffers if they haven't been set up yet

    // Bind the VAO and draw the line
    glBindVertexArray(VAO);

    // Check for potential OpenGL errors before drawing
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        LOG_ERROR("OpenGL error before drawing: 0x%X", error);
    }

    glDrawElements(GL_LINES, m_indexCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0); // Unbind the VAO after rendering
}

void TextureGenEngine::Line::ChangeColor(float r, float g, float b, float a)
{
    // Iterate through all vertices and update the color
    for (auto &vertex : m_vertices)
    {
        vertex.Color = glm::vec4(r, g, b, a); // Update color
    }

    // Re-upload the vertex data to the GPU with the updated color
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                                        // Bind the VBO
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(Vertex3D), &m_vertices[0]); // Update data
    glBindBuffer(GL_ARRAY_BUFFER, 0);                                                          // Unbind the VBO

    // Check for OpenGL errors
    int error = glGetError();
    if (error != GL_NO_ERROR)
    {
        LOG_WARN("Failed to update vertex buffer with new color: %d\n", error);
    }
}

bool TextureGenEngine::Line::CheckClickCollision(float x, float y)
{
    return false;
}

void TextureGenEngine::Line::UpdateEndPosition(float x, float y)
{
    m_vertices[1].Position = glm::vec3(x, y, 0.0f);                                            // Update the end position
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                                        // Bind the VBO
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(Vertex3D), &m_vertices[0]); // Update data
    glBindBuffer(GL_ARRAY_BUFFER, 0);                                                          // Unbind the VBO
}

void TextureGenEngine::Line::MoveStart(float x, float y)
{
    m_vertices[0].Position = m_vertices[0].Position + glm::vec3(x, -y, 0.0f);                  // Update the start position
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                                        // Bind the VBO
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(Vertex3D), &m_vertices[0]); // Update data
    glBindBuffer(GL_ARRAY_BUFFER, 0);                                                          // Unbind the VBO
}

void TextureGenEngine::Line::MoveEnd(float x, float y)
{
    m_vertices[1].Position = m_vertices[1].Position + glm::vec3(x, -y, 0.0f);                  // Update the end position
    glBindBuffer(GL_ARRAY_BUFFER, VBO);                                                        // Bind the VBO
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(Vertex3D), &m_vertices[0]); // Update data
    glBindBuffer(GL_ARRAY_BUFFER, 0);                                                          // Unbind the VBO
}
