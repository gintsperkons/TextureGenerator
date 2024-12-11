#include <Defines.h>
#include <string>
namespace TextureGenEngine
{
    class Shader
    {
    private:
        u32 m_ID;
        std::string m_name;

    public:
        Shader(std::string name, std::string vertexSource, std::string fragmentSource);
        void Use();
        ~Shader();
        u32 GetID() { return m_ID; }
        std::string GetName() { return m_name; }
    };

} // namespace TextureGenEngine
