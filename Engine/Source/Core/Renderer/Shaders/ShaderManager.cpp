#include "ShaderManager.h"
#include "Core/FileHandler/FileHandler.h"
#include "Shader.h"
#include "Core/Logger/Logger.h"

TextureGenEngine::ShaderManager::ShaderManager()
{
    m_shaders.insert(
        std::pair<std::string, Shader *>(
            "base",
            new Shader(ReadFile("Shaders/base.vert"), ReadFile("Shaders/base.frag"))));
    m_shaders.insert(
        std::pair<std::string, Shader *>(
            "text",
            new Shader(ReadFile("Shaders/text.vert"), ReadFile("Shaders/text.frag"))));
}

TextureGenEngine::Shader *TextureGenEngine::ShaderManager::GetShader(std::string name)
{
    if (m_shaders.find(name) != m_shaders.end()) return m_shaders[name];
    return nullptr;
}

TextureGenEngine::ShaderManager::~ShaderManager()
{
    for (auto &shaderPair : m_shaders)
    {
        delete shaderPair.second;
    }
    m_shaders.clear();
}
