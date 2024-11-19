#include "Defines.h"
#include "Core/GUI/SubElements/BaseElement.h"


namespace TextureGenEngine
{
    class Menu;
    class MenuBar: public BaseElement
    {
    private:
        
    public:
        TAPI MenuBar(/* args */);
        void Draw() override;
        void TAPI AddMenu(Menu* menu);
        ~MenuBar();
    };
} // namespace TextureGenEngine
