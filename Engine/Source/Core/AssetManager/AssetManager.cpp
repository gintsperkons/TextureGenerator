#include "AssetManager.h"
#include "Core/Renderer/Texture.h"
#include "Core/Logger/Logger.h"
#include "Engine.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

TextureGenEngine::AssetManager::AssetManager()
{
}

TextureGenEngine::AssetManager::~AssetManager()
{
  for (auto &texture : m_textures)
  {
    delete texture.second;
  }
  m_textures.clear();
}

TextureGenEngine::Texture *TextureGenEngine::AssetManager::LoadTexture(const char *fileName)
{
  if (m_textures.find(fileName) != m_textures.end())
  {
    return m_textures[fileName];
  }
  Texture *texture = new Texture();
  int width = 0, height = 0, channels = 0;
  unsigned char* data = stbi_load(("resources/textures/" + std::string(fileName)).c_str(), &width, &height, &channels, 0);
  texture->UpdateTexture(data, width, height, channels);
  stbi_image_free(data);
  m_textures[fileName] = texture;
  return texture;
}

TextureGenEngine::ImageData TextureGenEngine::AssetManager::LoadImage(const char *path)
{
  if (m_images.find(path) != m_images.end())
  {
    return m_images[path];
  }
  ImageData imgData = {};
  int width = 0, height = 0, channels = 0;
  imgData.data = stbi_load(("resources/textures/" + std::string(path)).c_str(), &width, &height, &channels, 0);
  imgData.width = width;
  imgData.height = height;
  imgData.channels = channels;
  LOG_DEBUG("Loaded image %s\n", path);
  LOG_DEBUG("Width: %d, Height: %d, Channels: %d\n", width, height, imgData.channels);
  return imgData;
}

TextureGenEngine::Texture *TextureGenEngine::LoadTexture(const char *path)
{
  if (Engine::Get() == nullptr)
  {
    LOG_ERROR("Engine is null\n");
    return nullptr;
  }
  if (Engine::Get()->GetAssetManager() == nullptr)
  {
    LOG_ERROR("AssetManager is null\n");
    return nullptr;
  }
  return TextureGenEngine::Engine::Get()->GetAssetManager()->LoadTexture(path);
}

TextureGenEngine::ImageData TextureGenEngine::LoadImage(const char *path)
{
  if (Engine::Get() == nullptr)
  {
    LOG_ERROR("Engine is null\n");
    return ImageData{};
  }
  if (Engine::Get()->GetAssetManager() == nullptr)
  {
    LOG_ERROR("AssetManager is null\n");
    return ImageData{};
  }
  return TextureGenEngine::Engine::Get()->GetAssetManager()->LoadImage(path);
}
