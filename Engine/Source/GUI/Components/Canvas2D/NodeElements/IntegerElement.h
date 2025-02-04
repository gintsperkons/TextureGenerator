#pragma once
#include "Defines.h"
#include "TextualInputElement.h"

namespace TextureGenEngine
{
   class IntegerElement : public TextualInputElement
   {
   private:
    /* data */
   public:
    TAPI IntegerElement(/* args */) ;
    TAPI void SetData(int data);
    TAPI void GetData(int &data);
    void UpdateData(std::string data) override {};
    void UpdateData(int data) override;
    virtual std::string ExportElementData() override;
      virtual void ImportElementData(std::string data) override;
    ~IntegerElement() ;
   };
} // namespace TextureGenEngine
