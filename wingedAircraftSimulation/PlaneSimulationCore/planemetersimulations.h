#ifndef PLANEMETERSIMULATIONS_H
#define PLANEMETERSIMULATIONS_H

#include "IAcceleroMeter_E.h"
#include "IGPS_E.h"
#include "IGyroMeter_E.h"
#include "IMagnetoMeter_E.h"
#include "IPressureSensor_E.h"

class SimAcceleroMeter  : public IAcceleroMeter_E
{
public:
    SimAcceleroMeter();
    virtual ~SimAcceleroMeter();
    virtual PlaneMeterID_E getId();
    virtual  void readValues();
    virtual  bool readComplete();

    virtual  int  accel_x();
    virtual  int  accel_y();
    virtual  int  accel_z();

    void setAccel_x(int a_x);
    void setAccel_y(int a_y);
    void setAccel_z(int a_z);
    void setReadState(bool read);
private:
    int mAccelX;
    int mAccelY;
    int mAccelZ;
    bool bValueRead;
};

class SimGPS  : public IGPS_E
{
public:
    SimGPS();
    virtual ~SimGPS();
    virtual PlaneMeterID_E getId();
    virtual  void readValues();
    virtual  bool readComplete();
    virtual double latitude();
    virtual double longitude();
    virtual double altitude();

    void setLatitude(double latit);
    void setLongitude(double longit);
    void setAltitude(double alti);
    void setReadState(bool read);
private:
    double mLati;
    double mLongi;
    double mAlti;
    bool bValueRead;
};

class SimGyroMeter  : public IGyroMeter_E
{
public:
    SimGyroMeter();
    virtual ~SimGyroMeter();
    virtual PlaneMeterID_E getId();
    virtual  void readValues();
    virtual  bool readComplete();
    virtual float pitch();
    virtual float roll();
    virtual float yaw();

    void setPitch(float Pitch);
    void setRoll(float Roll);
    void setYaw(float Yaw);
    void setReadState(bool read);
private:
    float mPitch;
    float mRoll;
    float mYaw;
    bool bValueRead;
};

class SimMagnetoMeter  : public IMagnetoMeter_E
{
public:
    SimMagnetoMeter();
    virtual ~SimMagnetoMeter();
    virtual PlaneMeterID_E getId();
    virtual  void readValues();
    virtual  bool readComplete();
    virtual double  heading();

    void setHeading(double heading);
    void setReadState(bool read);
private:
    double mHeading;
    bool bValueRead;
};

class SimPressureSensor  : public IPressureSensor_E
{
public:
    SimPressureSensor();
    virtual ~SimPressureSensor();
    virtual PlaneMeterID_E getId();
    virtual  void readValues();
    virtual  bool readComplete();
    virtual double  pressure();

    void setPressure(double Pressure);
    void setReadState(bool read);
private:
    double mPressure;
    bool bValueRead;
};


#endif // PLANEMETERSIMULATIONS_H
