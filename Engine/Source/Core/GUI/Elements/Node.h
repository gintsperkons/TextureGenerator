#include "Defines.h"
#include "Core/GUI/SubElements/BaseElement.h"

namespace TextureGenEngine
{
    class Mesh;
    class Node : public BaseElement
    {
    private:

        Mesh* m_background;
        /* data */
    public:
        TAPI Node(int x, int y);
        void Draw() override;
        void UpdatePositionByMouseDelta(double x, double y) override;
        ~Node();
    };
} // namespace TextureGenEngine