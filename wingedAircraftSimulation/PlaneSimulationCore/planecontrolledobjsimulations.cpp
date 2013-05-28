#include "planecontrolledobjsimulations.h"
#include <QDebug>

SimAileron::SimAileron()
{
    mAngle = 0;
    mPrevAngle = 0;
    bComplete = false;
}

SimAileron::~SimAileron()
{

}

ControlledObjID_E SimAileron::getId()
{
    return AILERON;
}

bool SimAileron::complete()
{
    return bComplete;
}

void SimAileron::cancelOperation()
{
    mAngle = mPrevAngle;
    bComplete = true;
}

void SimAileron::setAngle(float angle)
{
    mPrevAngle = mAngle;
    mAngle = angle;
    bComplete = false;

    qDebug() << "Aileron angle set to :" << mAngle;
}

float SimAileron::getAngle()
{
    return mAngle;
}

void SimAileron::setOperationComplete(bool bCompleted)
{
    bComplete = bCompleted;
}

////////////////////////////////////////////////////////////////

SimElevator::SimElevator()
{
    mAngle = 0;
    mPrevAngle = 0;
    bComplete = false;
}

SimElevator::~SimElevator()
{

}

ControlledObjID_E SimElevator::getId()
{
    return ELEVATOR;
}

bool SimElevator::complete()
{
    return bComplete;
}

void SimElevator::cancelOperation()
{
    mAngle = mPrevAngle;
    bComplete = true;
}

void SimElevator::setAngle(float angle)
{
    mPrevAngle = mAngle;
    mAngle = angle;
    bComplete = false;

    qDebug() << "Elevator angle set to :" << mAngle;
}

float SimElevator::getAngle()
{
    return mAngle;
}

void SimElevator::setOperationComplete(bool bCompleted)
{
    bComplete = bCompleted;
}

////////////////////////////////////////////////////////////////

SimEngine::SimEngine()
{
    bIsOn = false;
    bPrevState = false;
    bComplete = false;
}

SimEngine::~SimEngine()
{

}

ControlledObjID_E SimEngine::getId()
{
    return ENGINE;
}

bool SimEngine::complete()
{
    return bComplete;
}

void SimEngine::cancelOperation()
{
    bIsOn = bPrevState;
    bComplete = true;
}

void SimEngine::start()
{
    bPrevState = bIsOn;
    bIsOn = true;
    bComplete = false;  // Todo: needs to be modified.

    qDebug() << "Engine state set to :" << bIsOn;
}

void SimEngine::stop()
{
    bPrevState = bIsOn;
    bIsOn = false;
    bComplete = false;  // Todo: needs to be modified.
}

bool SimEngine::isOn()
{
    return bIsOn;
}

void SimEngine::setOperationComplete(bool bCompleted)
{
    bComplete = bCompleted;
}

void SimEngine::setState(bool bOn)
{
    bIsOn = bOn;    // Todo: needs to be modified.
}

////////////////////////////////////////////////////////////////

SimRudder::SimRudder()
{
    mAngle = 0;
    mPrevAngle = 0;
    bComplete = false;
}

SimRudder::~SimRudder()
{

}

ControlledObjID_E SimRudder::getId()
{
    return RUDDER;
}

bool SimRudder::complete()
{
    return bComplete;
}

void SimRudder::cancelOperation()
{
    mAngle = mPrevAngle;
    bComplete = true;
}

void SimRudder::setAngle(float angle)
{
    mPrevAngle = mAngle;
    mAngle = angle;
    bComplete = false;

    qDebug() << "Rudder angle set to :" << mAngle;
}

float SimRudder::getAngle()
{
    return mAngle;
}

void SimRudder::setOperationComplete(bool bCompleted)
{
    bComplete = bCompleted;
}

////////////////////////////////////////////////////////////////

SimThrust::SimThrust()
{
    mThrust = 0;
    mPevThrust = 0;
    bComplete = false;
}

SimThrust::~SimThrust()
{

}

ControlledObjID_E SimThrust::getId()
{
    return THRUST;
}

bool SimThrust::complete()
{
    return bComplete;
}

void SimThrust::cancelOperation()
{
    mThrust = mPevThrust;
    bComplete = true;
}

void SimThrust::setThrust(float perunit)
{
    mPevThrust = mThrust;
    mThrust = perunit;
    bComplete = false;

    qDebug() << "Thrust set to :" << mThrust;
}

float SimThrust::getThrust()
{
    return mThrust;
}

void SimThrust::setOperationComplete(bool bCompleted)
{
    bComplete = bCompleted;
}

////////////////////////////////////////////////////////////////

