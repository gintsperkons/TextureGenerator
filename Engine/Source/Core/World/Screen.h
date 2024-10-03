#pragma once
#include "Defines.h"
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
    TAPI void SetGUIController();
    ~Screen();
};
} // namespace TextureGenEngine


