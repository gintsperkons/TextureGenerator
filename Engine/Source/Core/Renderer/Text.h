#include "Defines.h"
#include <glm/glm.hpp>
#include <string>

namespace TextureGenEngine
{
    class Shader;
    class Text
    {
    private:
    unsigned int VBO, VAO;
    Shader *m_shader;
        /* data */
    public:
        Text(/* args */);
        void Draw(std::string text, float x, float y, float scale, glm::vec3 color);
        ~Text();
    };
    
} // namespace TextureGenEngine
