#include "Shader.h"
#include <glad/glad.h>
#include <cstddef>
#include <iostream>
#include "Core/Logger/Logger.h"
#include "Core/FileHandler/FileHandler.h"
#include <string>

TextureGenEngine::Shader::Shader(std::string name, std::string vertexSource, std::string fragmentSource)
{
    m_name = name;

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertexShaderSource = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        LOG_ERROR("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s", infoLog);
        LOG_ERROR("Shader name: %s", name.c_str());
        LOG_ERROR("Shader source: %s", vertexSource.c_str());
    }
    // Fragment

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentShaderSource = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        LOG_ERROR("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s", infoLog);
        LOG_ERROR("Shader name: %s", name.c_str());
        LOG_ERROR("Shader source: %s", fragmentSource.c_str());
    }

    // Shader Program
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexShader);
    glAttachShader(m_ID, fragmentShader);
    glLinkProgram(m_ID);
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_ID, 512, NULL, infoLog);
        LOG_ERROR("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void TextureGenEngine::Shader::Use()
{
    glUseProgram(m_ID);
}

TextureGenEngine::Shader::~Shader()
{
    glDeleteProgram(m_ID);
}
