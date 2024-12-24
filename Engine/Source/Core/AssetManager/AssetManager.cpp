#include "AssetManager.h"
#include "Engine.h"

TextureGenEngine::AssetManager::AssetManager()
{
}

TextureGenEngine::AssetManager::~AssetManager()
{
}


void TextureGenEngine::AssetManager::LoadTextFile(const char *path)
{
}

void TextureGenEngine::AssetManager::LoadImage(const char *path)
{
}

void TextureGenEngine::AssetManager::LoadFont(const char *path)
{
}

void TextureGenEngine::LoadTextFile(const char *path)
{
    TextureGenEngine::Engine::Get()->GetAssetManager()->LoadTextFile(path);
}

void TextureGenEngine::LoadImage(const char *path)
{
    TextureGenEngine::Engine::Get()->GetAssetManager()->LoadImage(path);
}

void TextureGenEngine::LoadFont(const char *path)
{
    TextureGenEngine::Engine::Get()->GetAssetManager()->LoadFont(path);
}
