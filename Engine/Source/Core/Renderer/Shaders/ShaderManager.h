#include <map>
#include <string>
namespace TextureGenEngine
{
    class Shader;
    class ShaderManager
    {
    private:
        std::map<std::string, TextureGenEngine::Shader *> m_shaders;

    public:
        ShaderManager(/* args */);
        Shader * GetShader(std::string name);
        ~ShaderManager();
    };
} // namespace TextureGenEngine
