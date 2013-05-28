#ifndef IGPS_E_H_INCLUDED
#define IGPS_E_H_INCLUDED

#include "IMeter_E.h"

class IGPS_E  : public IMeter_E
{
public:
          virtual ~IGPS_E() {}
          virtual double latitude()=0;
          virtual double longitude()=0;
          virtual double altitude()=0;
};

#endif // IGPS_E_H_INCLUDED
