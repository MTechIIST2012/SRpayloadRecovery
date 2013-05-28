#ifndef IMAGNETOMETER_E_H_INCLUDED
#define IMAGNETOMETER_E_H_INCLUDED

#include "IMeter_E.h"

class IMagnetoMeter_E  : public IMeter_E
{
public:
          virtual ~IMagnetoMeter_E() {}
          virtual double  heading()=0;
};

#endif // IMAGNETOMETER_E_H_INCLUDED
