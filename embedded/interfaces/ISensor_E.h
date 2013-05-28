#ifndef ISENSOR_E_H_INCLUDED
#define ISENSOR_E_H_INCLUDED

#include "planepartdefs.h"

class ISensor_E
{
public:
          virtual ~ISensor_E() {}
          virtual SensorID_E getId()=0;
};



#endif // ISENSOR_E_H_INCLUDED
