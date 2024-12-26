#version 330 core

in vec4 ourColor;       // Incoming color from vertex shader
in vec2 TexCoord;      // Incoming texture coordinates from vertex shader
out vec4 FragColor;    // Final fragment color output

uniform bool ourTextureExists; // Check if texture exists
uniform sampler2D ourTexture; // Texture to sample from

void main()
{
    if (ourTextureExists)
    {
        // Sample texture at normalized coordinates
         vec4 textureColor = texture(ourTexture, TexCoord);
         FragColor = vec4(ourColor.rgb, textureColor.a);
    }
    else 
    {
        // Fallback color if no texture
        FragColor = vec4(ourColor);
    }
}
