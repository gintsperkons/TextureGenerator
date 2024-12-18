#include "Defines.h"
#include "GUI/Components/Component.h"
#include <vector>

namespace TextureGenEngine
{
    class Line;
    class OutputConnector : public Component
    {
        std::vector<Line *> m_lines;
    public:
        OutputConnector();
        ~OutputConnector();
        void OnMouseDrag(double x, double y) override;
        void Draw() override;
    };
} // namespace TextureGenEngine