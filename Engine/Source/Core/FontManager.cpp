#include <glad/glad.h>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "FontManager.h"
#include "Core/Logger/Logger.h"

TextureGenEngine::FontManager::FontManager()
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        LOG_ERROR("ERROR::FREETYPE: Could not init FreeType Library\n");
        exit(-1);
    }

    FT_Face face;

    FT_Error error = FT_New_Face(ft, "resources/fonts/RobotoMono-Regular.ttf", 0, &face);
    if (error)
    {
        LOG_ERROR("FREETYPE: Failed to load font\n");
        fprintf(stderr, "Error code: %d\n", error);
        exit(-1);
    }

    FT_Set_Pixel_Sizes(face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++)
    {
        // Load char
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            LOG_ERROR("FREETYTPE : Failed to load Glyph");
            continue;
        }
        // Gen texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Store char
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x};
        m_characters.insert(std::pair<char, Character>(c, character));
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}
TextureGenEngine::FontManager::~FontManager()
{
}
