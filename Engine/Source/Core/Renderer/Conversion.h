#include "Defines.h"
#include <glm/glm.hpp>
#include "Engine.h"
#include "Core/Window/Window.h"
namespace TextureGenEngine
{
    glm::vec2 ScreenToRenderCords(float x, float y)
    {
        glm::vec2 result;
        int width, height;
        TextureGenEngine::Engine::Get()->GetWindow()->GetFramebufferSize(width, height);
        result.x = ((float)x / (float)width) * 2 - 1;
        result.y = ((float)y / (float)height) * 2 - 1;
        return result;
    }
}