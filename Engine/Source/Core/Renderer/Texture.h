#include "Defines.h"

namespace TextureGenEngine
{
    class Texture {
        int m_Width, m_Height, m_Channels;
        unsigned int m_TextureID;
        bool m_ready = false;
    public:
        Texture();
        ~Texture();

        void LoadTexture(const char* path);
        void BindTexture();
        void UnbindTexture();

        unsigned int GetTextureID() const { return m_TextureID; }
        int GetWidth() const { return m_Width; }
        int GetHeight() const { return m_Height; }
        bool IsReady() const { return m_ready; }
    };
} // namespace TextureGenEngine