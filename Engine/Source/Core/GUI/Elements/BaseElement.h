#include "Defines.h"
#include <vector>

namespace TextureGenEngine
{
    class Mesh;
    class BaseElement
    {
    protected:
        int m_x, m_y, m_width, m_height;
        std::vector<BaseElement*> m_children;
        Mesh *m_mesh;

    public:
        TAPI BaseElement(int x, int y, int width, int height) : m_x(x), m_y(y), m_width(width), m_height(height) {}
        virtual void Draw() = 0;
        virtual ~BaseElement() {
            delete m_mesh;
            for (BaseElement *child : m_children)
            {
                delete child;
            }
        };
    };
} // namespace TextureGenEngine
