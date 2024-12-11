#version 330 core

in vec3 ourColor;
in float outTime;
out vec4 FragColor;

void main()
{
    FragColor = vec4(ourColor, (sin(outTime*7)+1));
}