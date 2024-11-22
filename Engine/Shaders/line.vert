#version 330 core

layout(location = 0) in vec2 position; // Vertex position (x, y)
layout(location = 1) in vec3 color;    // Vertex color (r, g, b)
layout(location = 2) in vec2 texCoords; // Texture coordinates (u, v)

out vec3 vertexColor;  // Pass color to the fragment shader
out vec2 fragTexCoords; // Pass texture coordinates to the fragment shader

uniform mat4 model;        // Model transformation matrix
uniform mat4 projection;   // Projection matrix

void main()
{
    gl_Position = projection * model * vec4(position, 0.0, 1.0);

    vertexColor = color;      // Pass the vertex color
    fragTexCoords = texCoords; // Pass the texture coordinates
}
