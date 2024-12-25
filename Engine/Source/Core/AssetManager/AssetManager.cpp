#include "AssetManager.h"
#include "Core/Renderer/Texture.h"
#include "Core/Logger/Logger.h"
#include "Engine.h"

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
    texture->LoadTexture(("resources/texture/" + std::string(fileName)).c_str());
    m_textures[fileName] = texture;
    return texture;
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
