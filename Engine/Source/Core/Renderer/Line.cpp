#include "Line.h"
#include <glad/glad.h>
#include "Core/Logger/Logger.h"
#include "Core/Renderer/Shaders/Shader.h"
#include "Core/Asserts.h"
#include "Engine.h"
#include "Core/Renderer/Renderer.h"
#include <glm/gtc/type_ptr.hpp>

TextureGenEngine::Line::Line(Vertex2D start, Vertex2D end)
    : m_shader(nullptr), m_indexCount(2)
{
    // Initialize vertices with start and end points
    m_vertices.push_back(start);
    m_vertices.push_back(end);
    //!m_shader = TextureGenEngine::Engine::Get()->GetRenderer()->GetShader("line");
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
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex2D), &m_vertices[0], GL_STATIC_DRAW);

    // Element buffer setup
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], GL_STATIC_DRAW);

    // Vertex attribute pointer for position (location = 0)
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)offsetof(Vertex2D, Position));
    glEnableVertexAttribArray(0);

    // Vertex attribute pointer for color (location = 1)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)offsetof(Vertex2D, Color));
    glEnableVertexAttribArray(1);

    // Vertex attribute pointer for texCoords (location = 2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2D), (void *)offsetof(Vertex2D, TexCoords));
    glEnableVertexAttribArray(2);

    // Unbind VAO to avoid unintended modifications
    glBindVertexArray(0);
}

TextureGenEngine::Line::~Line()
{ // Delete OpenGL buffers when the Line object is destroyed
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
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
       //! glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(TextureGenEngine::Engine::Get()->GetRenderer()->GetProjectionMatrix()));
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
        vertex.Color = glm::vec3(r, g, b); // Update color (you can modify this to fit your needs)
    }

    // Re-upload the vertex data to the GPU with the updated color
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(Vertex2D), m_vertices.data());
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (glGetError() != GL_NO_ERROR)
    {
        LOG_ERROR("Failed to update vertex buffer with new color");
    }
}

bool TextureGenEngine::Line::CheckClickCollision(float x, float y)
{
    return false;
}
