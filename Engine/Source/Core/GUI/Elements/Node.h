#include "Defines.h"
#include "Core/GUI/SubElements/BaseElement.h"

namespace TextureGenEngine
{
    class Node : public BaseElement
    {
    private:
        /* data */
    public:
        TAPI Node(int x, int y, int width, int height);
        void Draw() override;
        ~Node();
    };
} // namespace TextureGenEngine