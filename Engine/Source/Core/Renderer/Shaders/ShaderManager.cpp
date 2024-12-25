#include "ShaderManager.h"
#include "Core/FileHandler/FileHandler.h"
#include "Shader.h"
#include "Core/Logger/Logger.h"

TextureGenEngine::ShaderManager::ShaderManager()
{
    m_shaders.insert(
        std::pair<std::string, Shader *>(
            "base",
            new Shader("base", ReadFile("Shaders/base.vert"), ReadFile("Shaders/base.frag"))));
    m_shaders.insert(
        std::pair<std::string, Shader *>(
            "text",
            new Shader("text", ReadFile("Shaders/text.vert"), ReadFile("Shaders/text.frag"))));
    m_shaders.insert(
        std::pair<std::string, Shader *>(
            "line",
            new Shader("line", ReadFile("Shaders/line.vert"), ReadFile("Shaders/line.frag"))));
    m_shaders.insert(
        std::pair<std::string, Shader *>(
            "cursor",
            new Shader("cursor", ReadFile("Shaders/cursor.vert"), ReadFile("Shaders/cursor.frag"))));
    m_shaders.insert(
        std::pair<std::string, Shader *>(
            "maskedColor",
            new Shader("maskedColor", ReadFile("Shaders/maskedColor.vert"), ReadFile("Shaders/maskedColor.frag"))));
}

TextureGenEngine::Shader *TextureGenEngine::ShaderManager::GetShader(std::string name)
{
    if (m_shaders.find(name) != m_shaders.end())
        return m_shaders[name];
    LOG_ERROR("Shader %s not found\n", name.c_str());
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
