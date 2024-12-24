#include "Defines.h"
#include "GUI/Components/Panel.h"

namespace TextureGenEngine
{
    class ScrollView : public Panel
    {
    public:
        TAPI ScrollView(float x, float y, float width, float height, ScalingType xScaling, ScalingType yScaling);
        void Draw() override;
        ~ScrollView();
    };
}