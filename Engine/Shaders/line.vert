#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 ourColor;

uniform mat4 projection;
uniform mat4 model;

void main()
{
    gl_Position = projection *   model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ourColor = aColor;
}