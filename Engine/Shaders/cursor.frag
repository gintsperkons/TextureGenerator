#version 330 core

in vec4 ourColor;
in float outTime;
out vec4 FragColor;

uniform bool ourTextureExists; // Check if texture exists
uniform sampler2D ourTexture; // Texture to sample from

void main()
{
     if (ourTextureExists)
    {
        // Sample texture at normalized coordinates
        FragColor = vec4(ourColor.bgr, (sin(outTime*7)+1));
    }
    else 
    {
        FragColor = vec4(ourColor.rgb, (sin(outTime*7)+1));
    }
}