#include "Defines.h"

namespace TextureGenEngine
{
    void LoadTextFile(const char *path);
    void LoadImage(const char *path);
    void LoadFont(const char *path);

    class AssetManager
    {
    private:
        /* data */
    public:
        AssetManager(/* args */);
        ~AssetManager();
        void LoadTextFile(const char *path);
        void LoadImage(const char *path);
        void LoadFont(const char *path);
    };
    

} // namespace TextureGenEngine
