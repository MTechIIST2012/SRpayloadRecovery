#ifndef IPRESSURESENSOR_H_INCLUDED
#define IPRESSURESENSOR_H_INCLUDED

#include "IMeter_E.h"

class IPressureSensor_E  : public IMeter_E
{
public:
          virtual ~IPressureSensor_E() {}
          virtual double  pressure()=0;
};

#endif // IPRESSURESENSOR_H_INCLUDED
