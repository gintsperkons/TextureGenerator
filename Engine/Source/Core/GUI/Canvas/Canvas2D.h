#include "Defines.h"
#include "Core/GUI/SubElements/BaseElement.h"

namespace TextureGenEngine
{
    class Canvas2D: public BaseElement
    {
    private:
        /* data */
    public:
        TAPI Canvas2D(int x, int y, int width, int height);
        void Draw() override;
        ~Canvas2D();
    };
} // namespace TextureGenEngine
