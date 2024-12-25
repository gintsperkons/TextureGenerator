#include "Texture.h"
#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Core/Logger/Logger.h"

TextureGenEngine::Texture::Texture()
{
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

TextureGenEngine::Texture::~Texture()
{
    m_ready = false;
    glDeleteTextures(1, &m_TextureID);
    m_TextureID = 0;
}

void TextureGenEngine::Texture::LoadTexture(const char *path)
{
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    unsigned char *data = stbi_load(path, &m_Width, &m_Height, &m_Channels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        m_ready = true;
    }
    else
    {
        LOG_ERROR("Failed to load texture");
        m_ready = false;
    }
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureGenEngine::Texture::BindTexture()
{
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void TextureGenEngine::Texture::UnbindTexture()
{
}
