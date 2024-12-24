#include "ObjectFactory.h"
#include "Core/Renderer/Mesh.h"
#include <cmath>
#include "Core/Renderer/Structures/Vertex3D.h"
#include "Core/Logger/Logger.h"
#include "Core/Renderer/Line.h"
#include "Core/Renderer/Bezier.h"

TextureGenEngine::Mesh* TextureGenEngine::ObjectFactory::CreateTriangle()
{
    Vertex3D vertices[] = {
        Vertex3D{ glm::vec3(0.5f,  0.5f,1.0f), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f) }, // top right
        Vertex3D{ glm::vec3(0.5f, -0.5f,1.0f), glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f) }, // bottom right
        Vertex3D{ glm::vec3(-0.5f, -0.5f,1.0f), glm::vec3(-0.5f, -0.5f, 1.0f), glm::vec2(0.0f, 0.0f) }  // bottom left
    };

    unsigned int indices[] = {
        0, 1, 2,   // first triangle
    };

    // Number of vertices and indices
    unsigned int vertexCount = sizeof(vertices) / sizeof(vertices[0]);
    unsigned int indexCount = sizeof(indices) / sizeof(indices[0]);
    return new Mesh(vertices, vertexCount, indices, indexCount);
}

TextureGenEngine::Mesh* TextureGenEngine::ObjectFactory::CreateSquare( float width, float height)
{
       Vertex3D vertices[] = {
        Vertex3D{glm::vec3(width, 0,0), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f)},   // top right
        Vertex3D{glm::vec3(width, height,0), glm::vec3(0.5f, -0.5f, 0.0f), glm::vec2(1.0f, 0.0f)},  // bottom right
        Vertex3D{glm::vec3(0, height,0), glm::vec3(-0.5f, -0.5f, 1.0f), glm::vec2(0.0f, 0.0f)}, // bottom left
        Vertex3D{glm::vec3(0, 0,0), glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec2(0.0f, 1.0f)}   // top left
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    // Number of vertices and indices
    unsigned int vertexCount = sizeof(vertices) / sizeof(vertices[0]);
    unsigned int indexCount = sizeof(indices) / sizeof(indices[0]);
    return new Mesh(vertices, vertexCount, indices, indexCount);
}


TextureGenEngine::Line *TextureGenEngine::ObjectFactory::CreateLine(float xStart, float yStart, float xEnd, float yEnd)
{
    Vertex3D start = Vertex3D{glm::vec3(xStart, yStart,0.1), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f)};
    Vertex3D end = Vertex3D{glm::vec3(xEnd, yEnd,0.1), glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(1.0f, 1.0f)};
    return new Line(start, end);
}

TextureGenEngine::Bezier* TextureGenEngine::ObjectFactory::CreateBezier(float xStart, float yStart, float xEnd, float yEnd, unsigned int segments)
{
    Vertex3D start = Vertex3D{glm::vec3(xStart, yStart,0.1), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)};
    Vertex3D end = Vertex3D{glm::vec3(xEnd, yEnd,0.1), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f)};
    return new Bezier(start,  end, segments);
}