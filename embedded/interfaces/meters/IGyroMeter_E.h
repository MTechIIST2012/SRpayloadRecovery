#ifndef IGYROMETER_E_H_INCLUDED
#define IGYROMETER_E_H_INCLUDED

#include "IMeter_E.h"

class IGyroMeter_E  : public IMeter_E
{
public:
          virtual ~IGyroMeter_E() {}
          virtual float pitch()=0;
          virtual float roll()=0;
          virtual float yaw()=0;
};

#endif // IGYROMETER_E_H_INCLUDED
