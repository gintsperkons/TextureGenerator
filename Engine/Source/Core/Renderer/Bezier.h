#pragma once
#include <vector>
#include "Structures/Vertex3D.h"

namespace TextureGenEngine
{
    class Shader;

    class Bezier
    {
    private:
        unsigned int VBO, VAO, EBO;       // OpenGL Buffers
        std::vector<Vertex3D> m_vertices; // Store two points (start and end)
        Vertex3D m_controlPoints[2];
        Vertex3D m_start;
        Vertex3D m_end;
        std::vector<unsigned int> m_indices; // Store index for drawing the Bezier
        glm::mat4 m_model;                   // Transformation matrix (position, rotation, scale)
        Shader *m_shader;                    // Shader to render the Bezier
        unsigned int m_indexCount;           // Index count
        unsigned int m_segments;             // Number of segments to approximate the Bezier

        Vertex3D CalculatePosition(Vertex3D start, Vertex3D end, float t);
        Vertex3D CalculateBezierPoint(Vertex3D start, Vertex3D end, float t, Vertex3D controlPoint1, Vertex3D controlPoint2);
        void RecalculateControls();
        void RecalculateCurve();

    public:
        // Constructor to initialize the Bezier with start and end points
        Bezier(Vertex3D start, Vertex3D end, unsigned int segments);

        // Destructor to cleanup OpenGL resources
        ~Bezier();

        // Draw the Bezier using the specified shader
        void Draw();

        // Change the color of the Bezier
        void ChangeColor(float r, float g, float b, float a);

        // Method to check if the Bezier was clicked (collision detection with point)
        bool CheckClickCollision(float x, float y);
        void UpdateEndPosition(float x, float y);
        void UpdateStartPosition(float x, float y);
        void MoveStart(float x, float y);
        void MoveEnd(float x, float y);
    };
}