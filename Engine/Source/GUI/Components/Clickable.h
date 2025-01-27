#pragma once
#include "Defines.h"
#include "GUI/Components/Component.h"
#include <functional>

namespace TextureGenEngine
{
    class Text;
    class Clickable : public Component
    {
        std::function<void()> m_onClick;
        std::string m_text;
        Text* m_textMesh;
    public:
        TAPI Clickable();
        void Draw() override;
        void Init(float width, float height) override;
        virtual ~Clickable();
        void Click(float x, float y) override;
        void OnHover(float x, float y) override;
        TAPI void SetText(std::string text) { m_text = text; }
        TAPI virtual void OnClick(std::function<void()> onClick);
    };
} // namespace TextureGenEngine