#ifndef IELEVATOR_E_H_INCLUDED
#define IELEVATOR_E_H_INCLUDED

#include "IControlledObj_E.h"

class IElevator_E : public IControlledObj_E
{
public:
          virtual ~IElevator_E() {}
          virtual void setAngle(float angle)=0;
          virtual float getAngle()=0;
};

#endif // IELEVATOR_E_H_INCLUDED
