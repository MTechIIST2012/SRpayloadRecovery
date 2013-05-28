#ifndef IMETER_E_H_INCLUDED
#define IMETER_E_H_INCLUDED

#include "planepartdefs.h"

class IMeter_E
{
public:
          virtual ~IMeter_E() {}
          virtual PlaneMeterID_E getId()=0;
          virtual  void readValues()=0;
          virtual  bool readComplete()=0;
};


#endif // IMETER_E_H_INCLUDED
