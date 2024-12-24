#include "Bezier.h"
#include <glad/glad.h>
#include "Core/Logger/Logger.h"
#include "Core/Renderer/Shaders/Shader.h"
#include "Core/Asserts.h"
#include "Engine.h"
#include "Core/Renderer/Renderer.h"
#include <glm/gtc/type_ptr.hpp>

TextureGenEngine::Bezier::Bezier(Vertex3D start, Vertex3D end, unsigned int segments)
    : m_shader(nullptr), m_indexCount(2)
{
    m_segments = segments;
    // Initialize vertices with start and end points
    m_start = start;
    m_end = end;
    RecalculateControls();
    for (unsigned int i = 0; i <= segments; ++i)
    {
        float t = static_cast<float>(i) / static_cast<float>(segments);
        Vertex3D center = CalculatePosition(m_start, m_end, 0.5);
        m_vertices.push_back(CalculateBezierPoint(m_start, m_end, t, m_controlPoints[0], m_controlPoints[1]));
    }
    m_shader = TextureGenEngine::Engine::Get()->GetRenderer()->GetShader("line");
    // Define indices for the Bezier (2 vertices make 1 Bezier)
    m_indices.clear();
    for (unsigned int i = 0; i < m_vertices.size(); ++i)
    {
        m_indices.push_back(i);
    }
    m_indexCount = static_cast<unsigned int>(m_vertices.size());

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
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *)offsetof(Vertex3D, Color));
    glEnableVertexAttribArray(1);

    // Vertex attribute pointer for texCoords (location = 2)
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void *)offsetof(Vertex3D, TexCoords));
    glEnableVertexAttribArray(2);
    glLineWidth(5.0f); // Set Bezier width to 3 pixels (can adjust as needed)

    // Unbind VAO to avoid unintended modifications
    glBindVertexArray(0);
}

TextureGenEngine::Bezier::~Bezier()
{ // Delete OpenGL buffers when the Bezier object is destroyed
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

Vertex3D TextureGenEngine::Bezier::CalculatePosition(Vertex3D start, Vertex3D end, float t)
{
    Vertex3D point;
    point.Color = glm::mix(start.Color, end.Color, t);             // Interpolate colors
    point.TexCoords = glm::mix(start.TexCoords, end.TexCoords, t); // Interpolate texture coordinates
    point.Position.x = (1 - t) * start.Position.x + t * end.Position.x;
    point.Position.y = (1 - t) * start.Position.y + t * end.Position.y;
    point.Position.z = (1 - t) * start.Position.z + t * end.Position.z;
    return point;
}

Vertex3D TextureGenEngine::Bezier::CalculateBezierPoint(Vertex3D start, Vertex3D end, float t, Vertex3D controlPoint1, Vertex3D controlPoint2)
{
    // Cubic Bezier curve formula
    float u = 1.0f - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    Vertex3D point;

    // Calculate the position using the cubic Bezier formula
    point.Position.x = uuu * start.Position.x +
                       3 * uu * t * controlPoint1.Position.x +
                       3 * u * tt * controlPoint2.Position.x +
                       ttt * end.Position.x;

    point.Position.y = uuu * start.Position.y +
                       3 * uu * t * controlPoint1.Position.y +
                       3 * u * tt * controlPoint2.Position.y +
                       ttt * end.Position.y;

    point.Position.z = 0.1f;

    // Interpolate colors and texture coordinates along the curve
    point.Color = glm::mix(start.Color, end.Color, t);             // Interpolate colors
    point.TexCoords = glm::mix(start.TexCoords, end.TexCoords, t); // Interpolate texture coordinates

    return point;
}

void TextureGenEngine::Bezier::RecalculateControls()
{
    int centerX = static_cast<int>((m_start.Position.x + m_end.Position.x) / 2.0f);
    int centerY = static_cast<int>((m_start.Position.y + m_end.Position.y) / 2.0f);
    m_controlPoints[0].Position = glm::vec3(centerX, m_start.Position.y, m_controlPoints[0].Position.z);
    m_controlPoints[1].Position = glm::vec3(centerX, m_end.Position.y, m_controlPoints[1].Position.z);
}

void TextureGenEngine::Bezier::RecalculateCurve()
{

    m_vertices.clear();

    // Loop through the segments, excluding the start and end points
    for (unsigned int i = 0; i <= m_segments; ++i)
    {
        float t = static_cast<float>(i) / static_cast<float>(m_segments);
        Vertex3D center = CalculatePosition(m_start, m_end, 0.5);
        m_vertices.push_back(CalculateBezierPoint(m_start, m_end, t, m_controlPoints[0], m_controlPoints[1]));
    }

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

    // Bind the VAO and draw the Bezier
    glBindVertexArray(VAO);

    // Check for potential OpenGL errors before drawing
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        LOG_ERROR("OpenGL error before drawing: 0x%X", error);
    }

    glDrawElements(GL_LINE_STRIP, m_indexCount, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0); // Unbind the VAO after rendering
}

void TextureGenEngine::Bezier::ChangeColor(float r, float g, float b, float a)
{
    // Iterate through all vertices and update the color
    for (auto &vertex : m_vertices)
    {
        vertex.Color = glm::vec3(r, g, b); // Update color
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

bool TextureGenEngine::Bezier::CheckClickCollision(float x, float y)
{
    return false;
}

void TextureGenEngine::Bezier::UpdateEndPosition(float x, float y)
{
    m_end.Position = glm::vec3(x, y, m_end.Position.z);
    RecalculateControls();
    RecalculateCurve();
}

void TextureGenEngine::Bezier::UpdateStartPosition(float x, float y)
{
    m_start.Position = glm::vec3(x, y, m_start.Position.z);
    RecalculateControls();
    RecalculateCurve();
}

void TextureGenEngine::Bezier::MoveStart(float x, float y)
{
    m_start.Position = m_start.Position + glm::vec3(x, -y, 0.1f);
    RecalculateControls();
    RecalculateCurve();
}

void TextureGenEngine::Bezier::MoveEnd(float x, float y)
{
    m_end.Position = m_end.Position + glm::vec3(x, -y, 0.1f);
    RecalculateControls();
    RecalculateCurve();
}
