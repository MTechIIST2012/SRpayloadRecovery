#ifndef PLANECONTROLLEDOBJSIMULATIONS_H
#define PLANECONTROLLEDOBJSIMULATIONS_H

#include "IAileron_E.h"
#include "IElevator_E.h"
#include "IEngine_E.h"
#include "IRudder_E.h"
#include "IThrust_E.h"

// Todo: needs to be given more reality by gradually changing values.(animation)

class SimAileron : public IAileron_E
{
public:
    SimAileron();
    virtual ~SimAileron();
    virtual ControlledObjID_E getId();
    virtual bool complete();
    virtual void cancelOperation();
    virtual void setAngle(float angle);
    virtual float getAngle();

    void setOperationComplete(bool bCompleted);
private:
    float mAngle;
    float mPrevAngle;
    bool bComplete;
};

class SimElevator : public IElevator_E
{
public:
    SimElevator();
    virtual ~SimElevator();
    virtual ControlledObjID_E getId();
    virtual bool complete();
    virtual void cancelOperation();
    virtual void setAngle(float angle);
    virtual float getAngle();

    void setOperationComplete(bool bCompleted);
private:
    float mAngle;
    float mPrevAngle;
    bool bComplete;
};

class SimEngine : public IEngine_E
{
public:
    SimEngine();
    virtual ~SimEngine();
    virtual ControlledObjID_E getId();
    virtual bool complete();
    virtual void cancelOperation();
    virtual void start();
    virtual void stop();
    virtual bool isOn();

    void setOperationComplete(bool bCompleted);
    void setState(bool bOn);
private:
    bool bIsOn;
    bool bPrevState;
    bool bComplete;
};

class SimRudder : public IRudder_E
{
public:
    SimRudder();
    virtual ~SimRudder();
    virtual ControlledObjID_E getId();
    virtual bool complete();
    virtual void cancelOperation();
    virtual void setAngle(float angle);
    virtual float getAngle();

    void setOperationComplete(bool bCompleted);
private:
    float mAngle;
    float mPrevAngle;
    bool bComplete;
};

class SimThrust : public IThrust_E
{
public:
    SimThrust();
    virtual ~SimThrust();
    virtual ControlledObjID_E getId();
    virtual bool complete();
    virtual void cancelOperation();
    virtual void setThrust(float perunit);
    virtual float getThrust();

    void setOperationComplete(bool bCompleted);
private:
    float mThrust;
    float mPevThrust;
    bool bComplete;
};


#endif // PLANECONTROLLEDOBJSIMULATIONS_H
