#pragma once
#include "Defines.h"
#include "NodeElement.h"
#include "NodeTypes.h"

namespace TextureGenEngine
{
    class TextureData;
    class Texture;
    class ImageInputElement : public NodeElement
    {
    private:
        std::vector<PatternGeneratorData> m_imageGenerationSequence;

    public:
        TAPI ImageInputElement(/* args */);
        ~ImageInputElement();
        virtual void Draw() override;
        virtual void Init(float width, float height) override;
        virtual void Setup(float x, float y) override;
        virtual void OnMouseDrag(float x, float y) override;
        virtual void UpdateData(std::vector<PatternGeneratorData> data);
        virtual void GetGenerationSequence(std::vector<PatternGeneratorData> &data)
        {
            data = m_imageGenerationSequence;
        }
    };

} // namespace TextureGenEngine
