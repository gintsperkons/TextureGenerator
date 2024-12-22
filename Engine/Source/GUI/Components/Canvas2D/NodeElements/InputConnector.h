#include "Defines.h"
#include "GUI/Components/Component.h"

namespace TextureGenEngine
{
    class Bezier;
    class InputConnector : public Component
    {
        Bezier *m_line = nullptr;
    public:
        InputConnector();

        void Draw() override;
        ~InputConnector();
        void ConnectLine(Bezier *line);
        void Move(float x, float y) override;
    };
} // namespace TextureGenEngine