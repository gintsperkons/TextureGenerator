#pragma once
#include "Defines.h"
#include "WindowEvents.h"
#include <string>
#include <vector>
#include "Core/Input/InputEvents.h"
#include <functional>

struct GLFWwindow;
namespace TextureGenEngine
{
    struct ResizeSub
    {
        std::function<void(ResizeEvent)> callback;
    };

    enum class Cursor
    {
        Arrow = 0x00036001,
        IBeam = 0x00036002,
        Crosshair = 0x00036003,
        PointingHand = 0x00036004,
        EWResize = 0x00036005,
        NSResize = 0x00036006,
        NWSEResize = 0x00036007,
        NESWResize = 0x00036008,
        ResizeAll = 0x00036009,
        NotAllowed = 0x0003600A,



    };

    class WindowManager;
    class GUIManager;
    class Renderer;
    class Input;
    class Window
    {
        std::vector<ResizeSub> m_resizeSubs;

        WindowManager *m_manager;
        int m_id;
        std::string m_title;
        int m_width;
        int m_height;
        GLFWwindow *m_window;
        GUIManager *m_gui;
        Input *m_input;

    public:
        bool ShouldClose();
        Window(WindowManager *manager, int id, const std::string &title, int width, int height, GLFWwindow *contextWindow = nullptr);
        ~Window();
        void Update();
        void Draw();
        void Resize(int width, int height);
        void Scissors(float x, float y, float width, float height);
        void ScissorsReset();
        void SetCursor(Cursor cursor);
        TAPI void AddGUI(GUIManager *gui);
        GLFWwindow *GetWindow() { return m_window; }
        int GetWidth() { return m_width; }
        int GetHeight() { return m_height; }
        void GetFramebufferSize(int &width, int &height);
        Input *GetInput() { return m_input; }
        std::vector<ResizeSub> GetResizeSubs() { return m_resizeSubs; }
    };
}
