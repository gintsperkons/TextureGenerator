#include "Defines.h"
#include "GUI/Components/Panel.h"
#include "GUI/Components/Component.h"
#include <vector>

namespace TextureGenEngine
{
    class Clickable;
    class ScrollView : public Panel
    {
        std::vector<Component *> m_elements;

    public:
        TAPI ScrollView(float x, float y, float width, float height, ScalingType xScaling, ScalingType yScaling);
        void Init(float width, float height) override;
        void Draw() override;
        void OnHover(float x, float y) override;
        void Resize(float width, float height) override;
        TAPI void AddElement(Component *element);
        Component *SelectObject(float x, float y) override;
        float GetItemOffset(Component *el);
        ~ScrollView();
    };
}