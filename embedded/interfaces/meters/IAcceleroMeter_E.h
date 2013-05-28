#ifndef IACCELEROMETER_E_H_INCLUDED
#define IACCELEROMETER_E_H_INCLUDED

#include "IMeter_E.h"

class IAcceleroMeter_E  : public IMeter_E
{
public:
          virtual ~IAcceleroMeter_E() {}
          virtual  int  accel_x()=0;
          virtual  int  accel_y()=0;
          virtual  int  accel_z()=0;
};



#endif // IACCELEROMETER_E_H_INCLUDED
