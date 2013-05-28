#ifndef IPLANE_E_INCLUDED
#define IPLANE_E_INCLUDED

#include "embedded_typedefs.h"
#include "planepartdefs.h"
#include "_LinkedList.h"

class IMeter_E;
class ISensor_E;
class IControlledObj_E;

class IPlane_E
{
public:
          virtual ~IPlane_E() {}

          // components.
          virtual IMeter_E* getMeter(PlaneMeterID_E id)=0;
          virtual ISensor_E* getSensor(SensorID_E id)=0;
          virtual IControlledObj_E* getControlledObj(ControlledObjID_E id)=0;

          // plane state
          virtual _PlaneState getState()=0;
          virtual bool requestFlyMode(_PlaneFlyMode mode)=0;
          virtual _PlaneFlyMode getFlyMode()=0;

          // operations.
          virtual void setPath( const  _LinkedList<_GPSPosition>& poslist)=0;
          virtual bool startEngine()=0;
          virtual void stopEngine()=0;
          virtual void fly()=0;
};



#endif // IPLANE_E_INCLUDED
