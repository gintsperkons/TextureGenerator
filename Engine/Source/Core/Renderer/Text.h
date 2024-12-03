#include "Defines.h"
#include <glm/glm.hpp>
#include <string>
#include "Core/Renderer/Structures/Aligment.h"

namespace TextureGenEngine
{
    class Shader;
    class Text
    {
    private:
        unsigned int VBO, VAO;
        Shader *m_shader;
        /* data */
        float CalculateScale(std::string text, int textSize, int &textHeight, int &textWidth, int &maxDescender);

    public:
        Text();
        void Draw(std::string text, float x, float y, int frameHeight, int frameWidth, int textSize, glm::vec3 color, AlignmentHorizontal hAlign, AlignmentVertical vAlign);
        ~Text();
    };

} // namespace TextureGenEngine
