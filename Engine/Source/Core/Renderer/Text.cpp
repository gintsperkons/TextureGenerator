#include <glad/glad.h>
#include "Text.h"
#include <algorithm>
#include <cstddef>
#include "Core/Renderer/Shaders/Shader.h"
#include "Core/Renderer/Renderer.h"
#include "Engine.h"
#include "Core/Logger/Logger.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Core/Font/FontManager.h"

TextureGenEngine::Text::Text(bool staticSize):m_staticSize(staticSize)
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


float TextureGenEngine::Text::CalculateScale(std::string text, float textSize, float &textHeight, float &textWidth, float &maxDescender)
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

        totalWidth += (ch.Advance >> 6);                               // Advance is in 1/64th pixels, convert to pixels
        hAboveBase = std::max((float)hAboveBase, (float)ch.Bearing.y); // Track the maximum height below the baseline
        hBelowBase = std::max((float)hBelowBase, (float)(ch.Size.y - ch.Bearing.y));
        maxDescender = std::min(maxDescender, (float)(ch.Bearing.y - ch.Size.y));
    }
    totalHeight = hAboveBase;
    textHeight = hAboveBase + hBelowBase;
    textWidth = totalWidth;
    // Calculate the maximum scale based on height (height constraint)
    
    if (m_staticSize )
    {
        if (textHeight == 0)
            return 1.0f;
        return (float)textSize / 30.0f;
    }
    return textSize / (lineCount * totalHeight);
}

void TextureGenEngine::Text::Draw(std::string text, float x, float y, int frameHeight, int frameWidth, int textSize, glm::vec3 color, AlignmentHorizontal hAlign, AlignmentVertical vAlign) // width and height in pixels of text
{
    m_shader->Use();
    if (glGetError() != GL_NO_ERROR)
    {
        LOG_ERROR("Shader use error");
    }

    GLint projectionLoc = glGetUniformLocation(m_shader->GetID(), "projection");
    GLint viewLoc = glGetUniformLocation(m_shader->GetID(), "view");
    GLint textColorLoc = glGetUniformLocation(m_shader->GetID(), "textColor");
    if (projectionLoc == -1 || textColorLoc == -1 || viewLoc == -1)
    {
        LOG_ERROR("Failed to get uniform location");
    }
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(TextureGenEngine::Engine::Get()->GetRenderer()->GetViewMatrix()));
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(TextureGenEngine::Engine::Get()->GetRenderer()->GetProjectionMatrix()));
    glUniform3f(textColorLoc, color.x, color.y, color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);
    float textHeight = 0;
    float textWidth = 0;
    float maxDescender = 0;
    float scale = CalculateScale(text,(float)textSize, textHeight, textWidth, maxDescender);
    std::string::const_iterator c;

    if(vAlign == AlignmentVertical::CENTER)
        y = y + (frameHeight - textSize) / 2; // VCenter
    else if(vAlign == AlignmentVertical::BOTTOM)
        y = y; //VBottom   
    else if(vAlign == AlignmentVertical::TOP)
        y = y + (frameHeight - textHeight * scale) - maxDescender * scale; // Adjust for descenders VTop

    if(hAlign == AlignmentHorizontal::CENTER)
        x = x + (frameWidth - textWidth * scale) / 2; // HCenter
    else if(hAlign == AlignmentHorizontal::LEFT)
        x= x; //HLeft
    else if(hAlign == AlignmentHorizontal::RIGHT)
        x = x + (frameWidth - textWidth * scale); //HRight
    

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

float TextureGenEngine::Text::GetTextWidth(std::string text, int textSize)
{
    int textWidth = 0;
    for (char c : text)
    {
        Character ch = TextureGenEngine::Engine::Get()->GetFontManager()->GetCharacter(c);
        textWidth += (ch.Advance >> 6);
    }
    return textWidth * textSize / 30.0f;
}
