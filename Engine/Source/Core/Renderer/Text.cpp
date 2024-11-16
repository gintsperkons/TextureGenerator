#include <glad/glad.h>
#include "Text.h"
#include <algorithm>
#include <cstddef>
#include "Core/Renderer/Shaders/Shader.h"
#include "Core/Renderer/Renderer.h"
#include "Core/FontManager.h"
#include "Engine.h"
#include "Core/Logger/Logger.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

TextureGenEngine::Text::Text()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    m_shader = TextureGenEngine::Engine::Get()->GetRenderer()->GetShader("text");
}

float TextureGenEngine::Text::CalculateScale(std::string text, int width, int height)
{
    float totalWidth = 0.0f;
    float totalHeight = 0.0f;
    int lineCount = 1; // To count the number of lines
    float hBelowBase = 0.f;
    float hAboveBase = 0.f;
    // Iterate over each character to calculate the text's width and height
    for (char c : text)
    {
        Character ch = TextureGenEngine::Engine::Get()->GetFontManager()->GetCharacter(c);

        // For newlines, increase line count and reset current line width
        if (c == '\n')
        {
            lineCount++;
            continue;
        }

        totalWidth += (ch.Advance >> 6);                       // Advance is in 1/64th pixels, convert to pixels
        hBelowBase = std::max((float)hBelowBase, (float)ch.Bearing.y); // Track the maximum height below the baseline
        hAboveBase = std::max((float)hAboveBase, (float)(ch.Size.y - ch.Bearing.y));
        
    }
    totalHeight = hAboveBase + hBelowBase;

    // Calculate the maximum scale based on height (height constraint)
    float scaleY = height / (lineCount * totalHeight);

    // Now calculate the scale for the width
    float scaleX = width / totalWidth;

    // The final scale is the smaller of the two scales to ensure the text fits in both dimensions
    return std::min(scaleX, scaleY);
}

void TextureGenEngine::Text::Draw(std::string text, float x, float y, int height, int width, glm::vec3 color) // width and height in pixels of text
{
    m_shader->Use();
    if (glGetError() != GL_NO_ERROR)
    {
        LOG_ERROR("Shader use error");
    }

    GLint projectionLoc = glGetUniformLocation(m_shader->GetID(), "projection");
    GLint textColorLoc = glGetUniformLocation(m_shader->GetID(), "textColor");
    if (projectionLoc == -1 || textColorLoc == -1)
    {
        LOG_ERROR("Failed to get uniform location");
    }


    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(TextureGenEngine::Engine::Get()->GetRenderer()->GetProjectionMatrix()));
    glUniform3f(textColorLoc, color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);
    float scale = CalculateScale(text, width, height);
    float maxDescender = 0.0f;
    std::string::const_iterator c;

    // Calculate the maximum descent of the text to adjust the position
    for (c = text.begin(); c != text.end(); ++c)
    {
        Character ch = TextureGenEngine::Engine::Get()->GetFontManager()->GetCharacter(*c);

        // Calculate the descender height of this character
        float descender = (ch.Bearing.y - ch.Size.y);
        maxDescender = std::min(maxDescender, descender); // Keep track of the max descent
    }
    y -= maxDescender * scale;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = TextureGenEngine::Engine::Get()->GetFontManager()->GetCharacter(*c);

        float xpos = x + ch.Bearing.x * scale;
        float ypos = (y - (ch.Size.y - ch.Bearing.y) * scale); // Adjusted to flip vertically

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;
        // update VBO for each character
        float vertices[6][4] = {
            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos, ypos, 0.0f, 1.0f},
            {xpos + w, ypos, 1.0f, 1.0f},

            {xpos, ypos + h, 0.0f, 0.0f},
            {xpos + w, ypos, 1.0f, 1.0f},
            {xpos + w, ypos + h, 1.0f, 0.0f}};
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        if (glGetError() != GL_NO_ERROR)
        {
        }
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
        if (glGetError() != GL_NO_ERROR)
        {
            LOG_ERROR("Buffer sub data error for character: %c", *c);
        }

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        if (glGetError() != GL_NO_ERROR)
        {
            LOG_ERROR("Draw arrays error for character: %c", *c);
        }
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

TextureGenEngine::Text::~Text()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
