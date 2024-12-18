#include "Defines.h"
#include "GUI/Components/Component.h"

namespace TextureGenEngine
{
    class Line;
    class InputConnector : public Component
    {
        Line *m_line = nullptr;
    public:
        InputConnector();

        void Draw() override;
        ~InputConnector();
        void ConnectLine(Line *line);
        void Move(float x, float y) override;
    };
} // namespace TextureGenEngine