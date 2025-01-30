#pragma once
#include "Defines.h"
#include "NodeElement.h"

namespace TextureGenEngine
{
    class Mesh;
    class TextInput;

    class TextualInputElement : public NodeElement
    {
    protected:
        TextInput *m_textInput;

    public:
        TAPI TextualInputElement();
        void Draw() override;
        virtual void SetManager(GUIManager *manager) override;
        virtual void Init(float width, float height) override;
        virtual void Setup(float x, float y) override;
        virtual void OnMouseDrag(float x, float y) override;
        virtual Component *SelectObject(float x, float y) override;
        void LockInput() override;
        void UnlockInput() override;
        TAPI void GetData(std::string &data);
        void UpdateData(std::string data) override;
        ~TextualInputElement();
    };
} // namespace TextureGenEngine
