#include <ft2build.h>
#include FT_FREETYPE_H
#include "FontManager.h"
#include "Core/Logger/Logger.h"

TextureGenEngine::FontManager::FontManager()
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        LOG_ERROR("ERROR::FREETYPE: Could not init FreeType Library");
        exit(-1);
    }

    FT_Face face;

    FT_Error error = FT_New_Face(ft, "resources/fonts/RobotoMono-Regular.ttf", 0, &face);
    if (error)
    {
        LOG_ERROR("ERROR::FREETYPE: Failed to load font");
        fprintf(stderr, "Error code: %d\n", error);
        exit(-1);
    }
}
TextureGenEngine::FontManager::~FontManager()
{
}
