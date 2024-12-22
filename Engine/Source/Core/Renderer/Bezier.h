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
        std::vector<Vertex3D> m_vertices; // Store vertices for the Bezier curve
        Vertex3D m_controlPoints[2];      // Store control points for the Bezier curve
        std::vector<unsigned int> m_indices;        // Store index for drawing the curve
        glm::mat4 m_model;                // Transformation matrix (position, rotation, scale)
        Shader *m_shader;                 // Shader to render the curve
        unsigned int m_indexCount;        // Index count
        unsigned int m_segments;          // Number of segments for drawing the curve

        // Function to calculate a point on the Bezier curve given t (from 0 to 1)
        Vertex3D CalculateBezierPoint(Vertex3D start, Vertex3D end, float t);
        void RecalculateCurve();
    public:
        // Constructor to initialize the curve with start, end, and control points
        Bezier(Vertex3D start, Vertex3D control1, Vertex3D control2, Vertex3D end, unsigned int segments = 100);

        // Destructor to cleanup OpenGL resources
        ~Bezier();

        // Draw the curve using the specified shader
        void Draw();

        // Change the color of the curve
        void ChangeColor(float r, float g, float b, float a);

        // Method to check if the curve was clicked (collision detection with point)
        bool CheckClickCollision(float x, float y);
        void UpdateControlPointPosition(int pointIndex, float x, float y);
        void UpdateEndPosition(float x, float y);
    };
}
