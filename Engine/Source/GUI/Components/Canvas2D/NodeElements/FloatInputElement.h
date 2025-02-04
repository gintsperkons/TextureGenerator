#pragma once
#include "Defines.h"
#include "TextualInputElement.h"

namespace TextureGenEngine
{
    class FloatInputElement: public TextualInputElement
    {
    private:
        /* data */
    public:
        TAPI FloatInputElement(/* args */);
        TAPI void SetData(float data);
        TAPI void GetData(float &data);
        void UpdateData(std::string data) override {};
        void UpdateData(float data) override;
        virtual std::string ExportElementData() override;
        virtual void ImportElementData(std::string data) override;
        ~FloatInputElement();
    };
    

    
} // namespace TextureGenEngine

