#include "Defines.h"

class BaseElement
{
protected:
    int x,y,width,height;
    
public:
    virtual void Draw() const = 0;
    virtual ~BaseElement() {};
};