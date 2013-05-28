#ifndef ITHRUST_H_INCLUDED
#define ITHRUST_H_INCLUDED

#include "IControlledObj_E.h"

class IThrust_E : public IControlledObj_E
{
public:
          virtual ~IThrust_E() {}
          virtual void setThrust(float perunit)=0;
          virtual float getThrust()=0;
};

#endif // ITHRUST_H_INCLUDED
