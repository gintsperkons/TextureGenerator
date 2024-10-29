#pragma once
namespace TextureGenEngine
{
    class Mesh;
    class GUIManager;
class Screen
{
    Mesh* m_mesh;
    GUIManager* m_guiManager;
    
    public:
    Screen();
    void Update();
    void Draw();
    void SetGUIManager(GUIManager* guiManager);
    ~Screen();
};
} // namespace TextureGenEngine


