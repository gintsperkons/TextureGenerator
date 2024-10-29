#include <Defines.h>
#include <string>
namespace TextureGenEngine
{
    class Shader
    {
    private:
        u32 ID;

    public:
        Shader(std::string vertexSource, std::string fragmentSource);
        void Use();
        ~Shader();
    };

} // namespace TextureGenEngine
