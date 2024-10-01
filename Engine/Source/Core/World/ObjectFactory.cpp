#include "ObjectFactory.h"
#include "Core/Renderer/Mesh.h"
#include <cmath>
#include "Core/Renderer/Structures/Vertex2D.h"
#include "Core/Logger/Logger.h"

TextureGenEngine::Mesh* TextureGenEngine::ObjectFactory::CreateTriangle()
{
    Vertex2D vertices[] = {
        Vertex2D{ glm::vec2(0.5f,  0.5f), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f) }, // top right
        Vertex2D{ glm::vec2(0.5f, -0.5f), glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f) }, // bottom right
        Vertex2D{ glm::vec2(-0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, 1.0f), glm::vec2(0.0f, 0.0f) }  // bottom left
    };

    unsigned int indices[] = {
        0, 1, 2,   // first triangle
    };

    // Number of vertices and indices
    unsigned int vertexCount = sizeof(vertices) / sizeof(vertices[0]);
    unsigned int indexCount = sizeof(indices) / sizeof(indices[0]);
    return new Mesh(vertices, vertexCount, indices, indexCount);
}

TextureGenEngine::Mesh* TextureGenEngine::ObjectFactory::CreateSquare()
{
    Vertex2D vertices[] = {
        Vertex2D{ glm::vec2(0.5f,  0.5f), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f) }, // top right
        Vertex2D{ glm::vec2(0.5f, -0.5f), glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f) }, // bottom right
        Vertex2D{ glm::vec2(-0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, 1.0f), glm::vec2(0.0f, 0.0f) },  // bottom left
        Vertex2D{ glm::vec2(-0.5f,  0.5f), glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f) }   // top left
    };

    unsigned int indices[] = {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    // Number of vertices and indices
    unsigned int vertexCount = sizeof(vertices) / sizeof(vertices[0]);
    unsigned int indexCount = sizeof(indices) / sizeof(indices[0]);
    return new Mesh(vertices, vertexCount, indices, indexCount);
}

TextureGenEngine::Mesh* TextureGenEngine::ObjectFactory::CreateCircle()
{
    //// Number of segments to approximate the circle (e.g., 360 for smooth)
    //const int segments = 5;
    //const float radius = 1.0f; // Radius of the circle

    //// Vertices: 1 center point + 'segments' edge points
    //float vertices[(segments + 1) * 3];
    //unsigned int indices[segments * 3] {
    //    0, 1, 2,   // first triangle
    //        0, 2, 3,   // second triangle
    //        0, 3, 4,   // third triangle
    //        0, 4, 5,   // fourth triangle
    //        0, 5, 1    // fifth triangle
    //}; // Each triangle has 3 indices

    //// Center of the circle
    //vertices[0] = 0.0f; // x
    //vertices[1] = 0.0f; // y
    //vertices[2] = 0.0f; // z

    //// Generating vertices along the circumference
    //for (int i = 0; i < segments; i++)
    //{
    //    float angle = 2.0f * 3.14159f * i / segments;

    //    // Calculate the vertex position
    //    vertices[(i + 1) * 3] = radius * cos(angle); // x
    //    vertices[(i + 1) * 3 + 1] = radius * sin(angle); // y
    //    vertices[(i + 1) * 3 + 2] = 0.0f; // z

    //    //// Calculate the indices for the triangle fan
    //    //indices[i * 3] = 0; // Center point
    //    //indices[i * 3 + 1] = i + 1; // Current point
    //    //indices[i * 3 + 2] = (i + 2) % segments +1; // Next point



    //    LOG_DEBUG("Angle: %f\n", angle);
    //    LOG_DEBUG("Vertex %d: %f, %f, %f\n", i, vertices[(i + 1) * 3], vertices[(i + 1) * 3 + 1], vertices[(i + 1) * 3 + 2]);
    //}

    //// Number of vertices and indices
    //unsigned int vertexCount = sizeof(vertices) / sizeof(vertices[0]);
    //unsigned int indexCount = sizeof(indices) / sizeof(indices[0]);

    //// Return the new Mesh object
    //return new Mesh(vertices, vertexCount, indices, indexCount);
    return nullptr;
}

