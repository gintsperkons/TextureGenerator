#include "Texture.h"
#include <glad/glad.h>
#include <Core/AssetManager/AssetManager.h>
#include "Core/Logger/Logger.h"
#include "TextureData.h"

TextureGenEngine::Texture::Texture()
{
    glGenTextures(1, &m_TextureID);
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);     // Set wrapping for the S axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);     // Set wrapping for the T axis
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Minification filter
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Magnification filter

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
    ImageData imgData = TextureGenEngine::LoadImage(path);
    LOG_DEBUG("Loaded texture %s\n", path);
    LOG_DEBUG("Width: %d, Height: %d, Channels: %d\n", imgData.width, imgData.height, imgData.channels);
    if (imgData.data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgData.width, imgData.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData.data);
        glGenerateMipmap(GL_TEXTURE_2D);
        m_ready = true;
    }
    else
    {
        LOG_ERROR("Failed to load texture");
        m_ready = false;
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureGenEngine::Texture::LoadTexture(TextureData *data)
{
    m_Channels = data->GetChannels();
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data->GetWidth(), data->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data->GetRawData());
    glGenerateMipmap(GL_TEXTURE_2D);
    m_ready = true;
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureGenEngine::Texture::UpdateTexture(TextureData *data)
{
    if (data->Valid() == false) return;
    LOG_DEBUG("Updating texture with width %d and height %d size %d\n", data->GetWidth(), data->GetHeight(), data->GetPixels().size());
    m_Channels = data->GetChannels();
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, data->GetWidth(), data->GetHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, data->GetRawData());
    glGenerateMipmap(GL_TEXTURE_2D);
    m_ready = true;
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureGenEngine::Texture::UpdateTexture(unsigned char *data, int width, int height, int channels)
{
  glBindTexture(GL_TEXTURE_2D, m_TextureID);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureGenEngine::Texture::BindTexture()
{
    glBindTexture(GL_TEXTURE_2D, m_TextureID);
}

void TextureGenEngine::Texture::UnbindTexture()
{
}
