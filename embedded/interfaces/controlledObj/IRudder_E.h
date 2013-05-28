#ifndef IRUDDER_E_H_INCLUDED
#define IRUDDER_E_H_INCLUDED

#include "IControlledObj_E.h"

class IRudder_E : public IControlledObj_E
{
public:
          virtual ~IRudder_E() {}
          virtual void setAngle(float angle)=0;
          virtual float getAngle()=0;
};

#endif // IRUDDER_E_H_INCLUDED
