#pragma once
#include <vector>
#include "Structures/Vertex3D.h"

namespace TextureGenEngine
{
    class Shader;

    class Line
    {
    private:
        unsigned int VBO, VAO, EBO;          // OpenGL Buffers
        std::vector<Vertex3D> m_vertices;    // Store two points (start and end)
        std::vector<unsigned int> m_indices; // Store index for drawing the line
        glm::mat4 m_model;                   // Transformation matrix (position, rotation, scale)
        Shader *m_shader;                    // Shader to render the line
        unsigned int m_indexCount;           // Index count

    public:
        // Constructor to initialize the line with start and end points
        Line(Vertex3D start, Vertex3D end);

        // Destructor to cleanup OpenGL resources
        ~Line();

        // Draw the line using the specified shader
        void Draw();

        // Change the color of the line
        void ChangeColor(float r, float g, float b, float a);

        // Method to check if the line was clicked (collision detection with point)
        bool CheckClickCollision(float x, float y);
    };
}