#include "Bezier.h"
#include <glad/glad.h>
#include "Core/Logger/Logger.h"
#include "Core/Renderer/Shaders/Shader.h"
#include "Core/Asserts.h"
#include "Engine.h"
#include "Core/Renderer/Renderer.h"
#include <glm/gtc/type_ptr.hpp>

TextureGenEngine::Bezier::Bezier(Vertex3D start, Vertex3D control1, Vertex3D control2, Vertex3D end, unsigned int segments)
    : m_shader(nullptr), m_indexCount(0), m_segments(segments)
{
    // Initialize the start, control, and end points
    m_controlPoints[0] = control1;
    m_controlPoints[1] = control2;
    m_vertices.push_back(start);

    // Generate vertices for the Bezier curve based on the number of segments
    for (unsigned int i = 0; i < segments; ++i)
    {
        float t = static_cast<float>(i) / static_cast<float>(segments);
        m_vertices.push_back(CalculateBezierPoint(start, end, t));
    }

    m_vertices.push_back(end); // Add the end point

    // Set the shader
    m_shader = TextureGenEngine::Engine::Get()->GetRenderer()->GetShader("line");

    // Create OpenGL buffers
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Vertex buffer setup
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex3D), &m_vertices[0], GL_STATIC_DRAW);

    // Element buffer setup (we'll use lines to draw the curve)
    m_indices.resize(m_vertices.size());
    for (unsigned int i = 0; i < m_vertices.size(); ++i)
    {
        m_indices[i] = i;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), m_indices.data(), GL_STATIC_DRAW);

    // Set up the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *)offsetof(Vertex3D, Position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *)offsetof(Vertex3D, Color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *)offsetof(Vertex3D, TexCoords));
    glEnableVertexAttribArray(2);

    // Set line width for rendering
    glLineWidth(5.0f);

    glBindVertexArray(0); // Unbind VAO
}

TextureGenEngine::Bezier::~Bezier()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

Vertex3D TextureGenEngine::Bezier::CalculateBezierPoint(Vertex3D start, Vertex3D end, float t)
{
    // Quadratic Bezier curve formula
    float u = 1.0f - t;
    float tt = t * t;
    float uu = u * u;

    Vertex3D point;
    point.Position = start.Position * uu + 2 * u * t * m_controlPoints[0].Position + tt * end.Position;
    point.Color = glm::mix(start.Color, end.Color, t);             // Interpolate colors
    point.TexCoords = glm::mix(start.TexCoords, end.TexCoords, t); // Interpolate texture coordinates

    return point;
}

void TextureGenEngine::Bezier::RecalculateCurve()
{
    // Recalculate the curve vertices based on the updated end point
    Vertex3D start = m_vertices[0];                   // Start point
    Vertex3D end = m_vertices[m_vertices.size() - 1]; // End point

    m_vertices.clear();
    m_vertices.push_back(start); // Start point

    // Loop through the segments, excluding the start and end points
    for (unsigned int i = 1; i < m_segments; ++i)
    { // Start at 1 to skip start point
        float t = static_cast<float>(i) / static_cast<float>(m_segments);
        m_vertices.push_back(CalculateBezierPoint(start, end, t));
    }

    m_vertices.push_back(end); // End point, add it only once

    // Rebuild the indices based on the new vertices
    m_indices.clear();
    for (unsigned int i = 0; i < m_vertices.size(); ++i)
    {
        m_indices.push_back(i);
    }

    // Check for any OpenGL errors before updating buffers
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        LOG_ERROR("OpenGL error before updating buffer: 0x%X", error);
    }

    // Update the vertex buffer with the new vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(Vertex3D), &m_vertices[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Unbind the buffer

    // Update the index buffer with the new indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, m_indices.size() * sizeof(unsigned int), m_indices.data());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Unbind the buffer

    // Check for OpenGL errors after buffer update
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        LOG_ERROR("OpenGL error after updating buffer: 0x%X", error);
    }
}

void TextureGenEngine::Bezier::Draw()
{
    if (!m_shader)
    {
        LOG_ERROR("Shader is not set. Aborting draw call.");
        return;
    }

    LOG_INFO("Drawing Bezier curve");

    m_shader->Use();

    GLint projectionLoc = glGetUniformLocation(m_shader->GetID(), "projection");
    GLint modelLoc = glGetUniformLocation(m_shader->GetID(), "model");

    if (projectionLoc != -1)
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(TextureGenEngine::Engine::Get()->GetRenderer()->GetProjectionMatrix()));

    if (modelLoc != -1)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(m_model));

    glBindVertexArray(VAO);
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        LOG_ERROR("OpenGL error before drawing: 0x%X", error);
    }
    LOG_INFO("Drawing with %d vertices.\n", m_vertices.size());

    glDrawElements(GL_LINE_STRIP, m_indices.size(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void TextureGenEngine::Bezier::ChangeColor(float r, float g, float b, float a)
{
    for (auto &vertex : m_vertices)
    {
        vertex.Color = glm::vec3(r, g, b); // Update color
    }

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(Vertex3D), &m_vertices[0]);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

bool TextureGenEngine::Bezier::CheckClickCollision(float x, float y)
{
    // Implement collision detection if needed
    return false;
}

void TextureGenEngine::Bezier::UpdateControlPointPosition(int pointIndex, float x, float y)
{
    if (pointIndex >= 0 && pointIndex < 2)
    {
        m_controlPoints[pointIndex].Position = glm::vec3(x, y, 0.0f);
        RecalculateCurve();
    }
}

void TextureGenEngine::Bezier::UpdateEndPosition(float x, float y)
{
    m_vertices[m_vertices.size() - 1].Position = glm::vec3(x, y, 0.0f);
    RecalculateCurve();
}
