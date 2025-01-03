#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

out vec4 ourColor;
out float outTime;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
uniform float time;

void main()
{
    gl_Position = projection* view*model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    ourColor = aColor;
    outTime = time;
}