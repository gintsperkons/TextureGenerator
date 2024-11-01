#pragma once
#include "Defines.h"
namespace TextureGenEngine
{
    class Mesh;
    class GUIManager;
    class Text;
class Screen
{
    Text* m_textMesh;
    GUIManager* m_guiManager;
    
    public:
    Screen();
    void Update();
    void Draw();
    TAPI void SetGUIManager(GUIManager* guiManager);
    ~Screen();
    void Resize(int width, int height);
};
} // namespace TextureGenEngine


