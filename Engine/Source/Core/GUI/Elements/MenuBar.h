#include "Defines.h"
#include "BaseElement.h"


namespace TextureGenEngine
{
    class MenuBar: public BaseElement
    {
    private:
        /* data */
    public:
        TAPI MenuBar(/* args */);
        void Draw() override;
        ~MenuBar();
    };
} // namespace TextureGenEngine
