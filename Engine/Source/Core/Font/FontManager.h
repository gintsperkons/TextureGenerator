#include <glm/glm.hpp>
#include <map>
namespace TextureGenEngine
{
    struct Character
    {
        unsigned int TextureID;
        glm::ivec2 Size;
        glm::ivec2 Bearing;
        unsigned int Advance;
    };

    class FontManager
    {
    private:
        std::map<char, Character> m_characters;

    public:
        FontManager(/* args */);
        ~FontManager();
        Character GetCharacter(char c) { return m_characters[c]; };
    };
}
