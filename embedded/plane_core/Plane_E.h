#ifndef PLANE_E_H
#define PLANE_E_H

#include "IPlane_E.h"

class IControllerPipe;

class IGPS_E;
class IAcceleroMeter_E;
class IMagnetoMeter_E;
class IGyroMeter_E;
class IPressureSensor_E;

class IAileron_E;
class IElevator_E;
class IEngine_E;
class IRudder_E;
class IThrust_E;

class IPathPlanner_E;

struct PlaneMeterSet_E
{
          IGPS_E*  gps;
          IAcceleroMeter_E*  accelerometer;
          IMagnetoMeter_E*  magnetometer;
          IGyroMeter_E* gyrometer;
          IPressureSensor_E* pressuresensor;

          PlaneMeterSet_E();
          ~PlaneMeterSet_E();
};

struct PlaneControlledObjSet_E
{
          IAileron_E* alieron;
          IElevator_E* elevator;
          IEngine_E* engine;
          IRudder_E* rudder;
          IThrust_E* thrust;

          PlaneControlledObjSet_E();
          ~PlaneControlledObjSet_E();
};

struct PlaneSensorSet_E
{
          PlaneSensorSet_E();
          ~PlaneSensorSet_E();
};

class Plane_E  : public IPlane_E
{
public:
          Plane_E(PlaneMeterSet_E meters,
                  PlaneControlledObjSet_E  controlledObjs,
                  PlaneSensorSet_E  sensors,
                  IPathPlanner_E* pathplanner,
                  IControllerPipe* controllerPipe);
          virtual ~Plane_E();

          // components.
          virtual IMeter_E* getMeter(PlaneMeterID_E id);
          virtual ISensor_E* getSensor(SensorID_E id);
          virtual IControlledObj_E* getControlledObj(ControlledObjID_E id);

          // plane state
          virtual _PlaneState getState();
          virtual bool requestFlyMode(_PlaneFlyMode mode);
          virtual _PlaneFlyMode getFlyMode();

          // operations.
          virtual void setPath( const  _LinkedList<_GPSPosition>&  poslist);
          virtual bool startEngine();
          virtual void stopEngine();
          virtual void fly();
private:
          PlaneMeterSet_E mMeterSet;
          PlaneControlledObjSet_E mControlledObjSet;
          PlaneSensorSet_E  mSensorSet;
          _PlaneState mPlaneState;
          _PlaneFlyMode mPlaneFlyMode;
          IPathPlanner_E* mPathPlanner;
          IControllerPipe* mControllerPipe;
};

#endif // PLANE_E_H
