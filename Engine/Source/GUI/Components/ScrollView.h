#include "Defines.h"
#include "GUI/Components/Panel.h"

namespace TextureGenEngine
{
    class ScrollView : public Panel
    {
    public:
        TAPI ScrollView(int x, int y, int width, int height, ScalingType xScaling, ScalingType yScaling);
        void Draw() override;
        ~ScrollView();
    };
}