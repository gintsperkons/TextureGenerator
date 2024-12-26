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
        bool m_staticSize;
        unsigned int VBO, VAO;
        Shader *m_shader;
        /* data */
        float CalculateScale(std::string text, float textSize, float &textHeight, float &textWidth, float &maxDescender); 

    public:
        Text(bool staticSize = true);
        void Draw(std::string text, float x, float y, int frameHeight, int frameWidth, int textSize, AlignmentHorizontal hAlign = AlignmentHorizontal::CENTER, AlignmentVertical vAlign = AlignmentVertical::CENTER,glm::vec4 color = {1.0f,1.0f,1.0f,1.0f});
        ~Text();
        float GetTextWidth(std::string text, int textSize);
    };

} // namespace TextureGenEngine
