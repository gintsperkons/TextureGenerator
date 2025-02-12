#include "Defines.h"
#include <map>
#include <string>

namespace TextureGenEngine
{
  struct ImageData
  {
    int width = 0;
    int height = 0;
    int channels = 0;
    unsigned char *data;
  };

  class Texture;
  Texture *LoadTexture(const char *path);
  ImageData LoadImage(const char *path);
  class AssetManager
  {
  private:
    std::map<std::string, Texture *> m_textures;
    std::map<std::string, ImageData> m_images;
    /* data */
  public:
    AssetManager(/* args */);
    ~AssetManager();
    Texture *LoadTexture(const char *fileName);
    ImageData LoadImage(const char *path);
  };

} // namespace TextureGenEngine
