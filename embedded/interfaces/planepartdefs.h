#ifndef PLANEPARTDEFS_H_INCLUDED
#define PLANEPARTDEFS_H_INCLUDED

enum PlaneMeterID_E
{
          UNKNOWN_METER = -1,
          GPS_E,
          ACCELEROMETER_E,
          MAGNETOMETER_E,
          GYROMETER_E,
          PRESSURE_SENSOR_E
};

enum SensorID_E
{
          UNKNOWN_SENSOR = -1
};

enum ControlledObjID_E
{
          UNKNOWN_CTRLOBJ = -1,
          AILERON,
          ELEVATOR,
          RUDDER,
          THRUST,
          ENGINE
};


#endif // PLANEPARTDEFS_H_INCLUDED
