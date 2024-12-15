#pragma once
#include "Defines.h"
#include "NodeElement.h"

namespace TextureGenEngine
{
    class TextInput;

    class TextualInputElement : public NodeElement
    {
    private:
        TextInput *m_textInput;

    public:
        TAPI TextualInputElement();
        void Draw() override;
        virtual void SetManager(GUIManager *manager) override;
        virtual void Init(int width, int height) override;
        virtual void Setup(int x, int y) override;
        virtual void OnMouseDrag(double x, double y) override;
        virtual Component *SelectObject(double x, double y) override;
        ~TextualInputElement();
    };
} // namespace TextureGenEngine
