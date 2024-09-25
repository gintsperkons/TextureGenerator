#pragma once
namespace TextureGenEngine
{
    class Mesh;
class Screen
{
    Mesh* m_mesh;
    
    public:
    Screen();
    void Update();
    void Draw();
    ~Screen();
};
} // namespace TextureGenEngine


