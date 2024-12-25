#include "Defines.h"
#include <map>
#include <string>

namespace TextureGenEngine
{
    class Texture;
    Texture *LoadTexture(const char *path);
    class AssetManager
    {
    private:
        std::map<std::string, Texture *> m_textures;
        /* data */
    public:
        AssetManager(/* args */);
        ~AssetManager();
        Texture *LoadTexture(const char *fileName);
    };

} // namespace TextureGenEngine
