#include "Defines.h"
struct GLFWwindow;
namespace TextureGen
{
    class Window
    {
    private:
        GLFWwindow *m_window;
    public:
        TAPI Window(/* args */);
        TAPI Window(int width, int height, const char * title);
        TAPI void PollEvents();
        TAPI bool ShouldClose();
        TAPI ~Window();
    };

} // namespace TextureGen
