#include "Defines.h"
#include "GUI/Components/Component.h"
#include <vector>

namespace TextureGenEngine
{
    class Bezier;
    class OutputConnector : public Component
    {
        Bezier * m_line = nullptr;
        std::vector<Bezier *> m_lines;
    public:
        OutputConnector();
        ~OutputConnector();
        void OnMouseDrag(double x, double y) override;
        void Draw() override;
        void MouseRelease() override;
        void Move(float x, float y) override;
    };
} // namespace TextureGenEngine