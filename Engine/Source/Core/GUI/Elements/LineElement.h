#include "Defines.h"
#include "Core/GUI/SubElements/BaseElement.h"

namespace TextureGenEngine
{
    class Line;
    class LineElement : public BaseElement
    {
    private:
        Line *m_line;
        /* data */
    public:
        TAPI LineElement(int xStart, int yStart, int xEnd, int yEnd);
        void Draw() override;
        void UpdatePositionRelativeToParent(float x, float y);
        ~LineElement();
    };
}