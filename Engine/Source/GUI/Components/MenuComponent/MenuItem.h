#pragma once
#include "Defines.h"
#include "MenuComponent.h"
#include <functional>
#include <string>

namespace TextureGenEngine
{
  class Text;
  class MenuItem : public MenuComponent
  {
  private:
    std::string m_text;
    Text *m_textMesh;
    std::function<void()> m_onClick;

  public:
    TAPI MenuItem(std::string text, std::function<void()> onClick);
    ~MenuItem();
    void Init(float width, float height) override;
    void Draw() override;
    void Click(float x, float y) override;
    void OnHover(float x, float y) override;
  };

} // namespace TextureGenEngine
