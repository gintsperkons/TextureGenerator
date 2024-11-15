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
        float CalculateScale(std::string text, int width, int height);

    public:
        Text();
        void Draw(std::string text, float x, float y, int height, int width, glm::vec3 color);
        ~Text();
    };

} // namespace TextureGenEngine
