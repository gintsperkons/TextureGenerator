#pragma once
#include "Defines.h"
#include "Component.h"
#include <vector> 
#include <string>

namespace TextureGenEngine
{
  class Text;
  class Clickable;
  class Mesh;
  class Dropdown : public Component
  {
    std::vector<Component *> m_elements;
    Text * m_textMesh;
    Mesh *m_dropArrowDown;
    Mesh *m_dropArrowUp;
    bool m_opened = false;
    float m_titleHeight = 20;
    std::string m_text;

  public:
    TAPI Dropdown();
    ~Dropdown();
    void Draw() override;
    void Init(float width, float height) override;
    void OnHover(float x, float y) override;
    void Click(float x, float y) override;
    void Move(float x, float y) override;
    bool CheckCollision(float x, float y) override;
    TAPI void SetText(std::string text);
    void SetPosition(float x, float y) override;
    TAPI void AddElement(Component *element);
  };
} // namespace TextureGenEngine
