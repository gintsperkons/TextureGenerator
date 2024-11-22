#version 330 core

in vec3 vertexColor; // Interpolated vertex color from the vertex shader

out vec4 fragColor; // Final fragment color

void main()
{
    // Set the fragment color
    fragColor = vec4(vertexColor, 1.0); // Add an alpha of 1.0 for full opacity
}
