#version 330 core

layout (location = 0) in vec3 aPos;      // Position attribute
layout (location = 1) in vec4 aColor;    // Color attribute
layout (location = 2) in vec2 aTexCoord; // Texture coordinate attribute

out vec4 ourColor;  // Output color to fragment shader
out vec2 TexCoord;  // Output texture coordinates to fragment shader

uniform mat4 projection;  // Projection matrix
uniform mat4 model;       // Model transformation matrix
uniform mat4 view;        // View matrix

void main()
{
    // Apply model, view, and projection transformations
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    
    // Pass color and texture coordinates to fragment shader
    ourColor = aColor;
    TexCoord = aTexCoord;
}
