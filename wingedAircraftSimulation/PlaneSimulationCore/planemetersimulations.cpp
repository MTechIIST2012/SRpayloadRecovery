#include "planemetersimulations.h"


//UNKNOWN_METER = -1,
//GPS_E,
//ACCELEROMETER_E,
//MAGNETOMETER_E,
//GYROMETER_E,
//PRESSURE_SENSOR_E

SimAcceleroMeter::SimAcceleroMeter()
{
    mAccelX = 0;
    mAccelY = 0;
    mAccelZ = 0;
    bValueRead = false;
}

SimAcceleroMeter::~SimAcceleroMeter()
{

}

PlaneMeterID_E SimAcceleroMeter::getId()
{
    return ACCELEROMETER_E;
}

void SimAcceleroMeter::readValues()
{
    bValueRead = false;
}

bool SimAcceleroMeter::readComplete()
{
    return bValueRead;
}

int  SimAcceleroMeter::accel_x()
{
    return mAccelX;
}

int  SimAcceleroMeter::accel_y()
{
    return mAccelY;
}

int  SimAcceleroMeter::accel_z()
{
    return mAccelZ;
}

void SimAcceleroMeter::setAccel_x(int a_x)
{
    mAccelX = a_x;
}

void SimAcceleroMeter::setAccel_y(int a_y)
{
    mAccelY = a_y;
}

void SimAcceleroMeter::setAccel_z(int a_z)
{
    mAccelZ = a_z;
}

void SimAcceleroMeter::setReadState(bool read)
{
    bValueRead = read;
}

///////////////////////////////////////////////////////////////////

SimGPS::SimGPS()
{
    mLati = 0;
    mLongi = 0;
    mAlti = 0;
    bValueRead = false;
}

SimGPS::~SimGPS()
{

}

PlaneMeterID_E SimGPS::getId()
{
    return GPS_E;
}

void SimGPS::readValues()
{
    bValueRead = false;
}

bool SimGPS::readComplete()
{
    return bValueRead;
}

double SimGPS::latitude()
{
    return mLati;
}

double SimGPS::longitude()
{
    return mLongi;
}

double SimGPS::altitude()
{
    return mAlti;
}

void SimGPS::setLatitude(double latit)
{
    mLati = latit;
}

void SimGPS::setLongitude(double longit)
{
    mLongi = longit;
}

void SimGPS::setAltitude(double alti)
{
    mAlti = alti;
}

void SimGPS::setReadState(bool read)
{
    bValueRead = read;
}

///////////////////////////////////////////////////////////////////

SimGyroMeter::SimGyroMeter()
{
    mPitch = 0;
    mRoll = 0;
    mYaw = 0;
    bValueRead = false;
}

SimGyroMeter::~SimGyroMeter()
{

}

PlaneMeterID_E SimGyroMeter::getId()
{
    return GYROMETER_E;
}

void SimGyroMeter::readValues()
{
    bValueRead = false;
}

bool SimGyroMeter::readComplete()
{
    return bValueRead;
}

float SimGyroMeter::pitch()
{
    return mPitch;
}

float SimGyroMeter::roll()
{
    return mRoll;
}

float SimGyroMeter::yaw()
{
    return mYaw;
}

void SimGyroMeter::setPitch(float Pitch)
{
    mPitch = Pitch;
}

void SimGyroMeter::setRoll(float Roll)
{
    mRoll = Roll;
}

void SimGyroMeter::setYaw(float Yaw)
{
    mYaw = Yaw;
}

void SimGyroMeter::setReadState(bool read)
{
    bValueRead = read;
}

///////////////////////////////////////////////////////////////////

SimMagnetoMeter::SimMagnetoMeter()
{
    mHeading = 0;
    bValueRead = false;
}

SimMagnetoMeter::~SimMagnetoMeter()
{

}

PlaneMeterID_E SimMagnetoMeter::getId()
{
    return MAGNETOMETER_E;
}

void SimMagnetoMeter::readValues()
{
    bValueRead = false;
}

bool SimMagnetoMeter::readComplete()
{
    return bValueRead;
}

double SimMagnetoMeter::heading()
{
    return mHeading;
}

void SimMagnetoMeter::setHeading(double heading)
{
    mHeading = heading;
}

void SimMagnetoMeter::setReadState(bool read)
{
    bValueRead = read;
}

///////////////////////////////////////////////////////////////////

SimPressureSensor::SimPressureSensor()
{
    mPressure = 0;
    bValueRead = false;
}

SimPressureSensor::~SimPressureSensor()
{

}

PlaneMeterID_E SimPressureSensor::getId()
{
    return PRESSURE_SENSOR_E;
}

void SimPressureSensor::readValues()
{
    bValueRead = false;
}

bool SimPressureSensor::readComplete()
{
    return bValueRead;
}

double  SimPressureSensor::pressure()
{
    return mPressure;
}

void SimPressureSensor::setPressure(double Pressure)
{
    mPressure = Pressure;
}

void SimPressureSensor::setReadState(bool read)
{
    bValueRead = read;
}

///////////////////////////////////////////////////////////////////

