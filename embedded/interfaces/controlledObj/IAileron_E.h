#ifndef IAILERON_E_H_INCLUDED
#define IAILERON_E_H_INCLUDED

#include "IControlledObj_E.h"

class IAileron_E : public IControlledObj_E
{
public:
          virtual ~IAileron_E() {}
          virtual void setAngle(float angle)=0;
          virtual float getAngle()=0;
};

#endif // IAILERON_E_H_INCLUDED
