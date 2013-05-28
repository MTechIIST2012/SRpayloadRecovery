#include "Plane_E.h"
#include "IAcceleroMeter_E.h"
#include "IGPS_E.h"
#include "IGyroMeter_E.h"
#include "IMagnetoMeter_E.h"
#include "IPressureSensor_E.h"

#include "IAileron_E.h"
#include "IElevator_E.h"
#include "IEngine_E.h"
#include "IRudder_E.h"
#include "IThrust_E.h"

#include "IPathPlanner_E.h"
#include "IControllerPipe.h"

 PlaneMeterSet_E::PlaneMeterSet_E()
 {
          gps = 0;
          accelerometer = 0;
          magnetometer = 0;
          gyrometer = 0;
          pressuresensor = 0;
 }

 PlaneMeterSet_E::~PlaneMeterSet_E()
 {

 }

PlaneControlledObjSet_E::PlaneControlledObjSet_E()
{
          alieron = 0;
          elevator = 0;
          engine = 0;
          rudder = 0;
          thrust = 0;
}

PlaneControlledObjSet_E::~PlaneControlledObjSet_E()
{

}

PlaneSensorSet_E::PlaneSensorSet_E()
{

}

PlaneSensorSet_E::~PlaneSensorSet_E()
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Plane_E::Plane_E(PlaneMeterSet_E meters,
                 PlaneControlledObjSet_E  controlledObjs,
                 PlaneSensorSet_E  sensors,
                 IPathPlanner_E* pathplanner,
                 IControllerPipe* controllerPipe)
{
          mMeterSet = meters;
          mControlledObjSet = controlledObjs;
          mSensorSet = sensors;
          mPathPlanner = pathplanner;
          mControllerPipe = controllerPipe;
}

Plane_E::~Plane_E()
{
           if(mMeterSet.gps)
                    delete mMeterSet.gps;
          if(mMeterSet.accelerometer)
                    delete mMeterSet.accelerometer;
          if(mMeterSet.magnetometer)
                    delete mMeterSet.magnetometer;
          if(mMeterSet.gyrometer)
                    delete mMeterSet.gyrometer;
          if(mMeterSet.pressuresensor)
                    delete mMeterSet.pressuresensor;

          if(mControlledObjSet.alieron)
                    delete mControlledObjSet.alieron;
          if(mControlledObjSet.elevator)
                    delete mControlledObjSet.elevator;
          if(mControlledObjSet.engine)
                    delete mControlledObjSet.engine;
          if(mControlledObjSet.rudder)
                    delete mControlledObjSet.rudder;
          if(mControlledObjSet.thrust)
                    delete mControlledObjSet.thrust;
}


IMeter_E* Plane_E::getMeter(PlaneMeterID_E id)
{
          IMeter_E* meter = 0;
          switch(id)
          {
          case GPS_E:
                    meter = mMeterSet.gps;
                    break;
          case ACCELEROMETER_E:
                    meter = mMeterSet.accelerometer;
                    break;
          case MAGNETOMETER_E:
                    meter = mMeterSet.magnetometer;
                    break;
          case GYROMETER_E:
                    meter = mMeterSet.gyrometer;
                    break;
          case PRESSURE_SENSOR_E:
                    meter = mMeterSet.pressuresensor;
                    break;
          };
          return meter;
}

ISensor_E* Plane_E::getSensor(SensorID_E id)
{
          ISensor_E* sensor = 0;
          return sensor;
}

IControlledObj_E* Plane_E::getControlledObj(ControlledObjID_E id)
{
          IControlledObj_E* controlledObj = 0;
          switch(id)
          {
           case AILERON:
                    controlledObj = mControlledObjSet.alieron;
                    break;
           case ELEVATOR:
                    controlledObj = mControlledObjSet.elevator;
                    break;
           case RUDDER:
                    controlledObj = mControlledObjSet.rudder;
                    break;
           case THRUST:
                    controlledObj = mControlledObjSet.thrust;
                    break;
          };
          return controlledObj;
}

          // plane state
_PlaneState Plane_E::getState()
{
          return mPlaneState;
}

bool Plane_E::requestFlyMode(_PlaneFlyMode mode)        // Todo: Impliment
{
          return false;
}

_PlaneFlyMode Plane_E::getFlyMode()
{
          return mPlaneFlyMode;
}
          // operations.
void Plane_E::setPath( const  _LinkedList<_GPSPosition>&  poslist)
{
          mPathPlanner->setPath(poslist);
}

bool Plane_E::startEngine()         // Todo: needs to be modified.
{
          mControlledObjSet.engine->start();
          while(mControlledObjSet.engine->complete() == false);
          return true;
}

void Plane_E::stopEngine()
{
          mControlledObjSet.engine->stop();
          while(mControlledObjSet.engine->complete() == false);
}

void Plane_E::fly()                    // Todo: needs to be modified.
{
          if(1)//mControlledObjSet.engine->isOn())
          {
                     mControlledObjSet.thrust->setThrust(1);
                     mControlledObjSet.elevator->setAngle(-30);

                     //mControllerPipe->_delay(10000);
                     mControlledObjSet.elevator->setAngle(0);
          }
}
