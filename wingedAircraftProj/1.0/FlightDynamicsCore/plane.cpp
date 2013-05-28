#include "plane.h"
#include "PlanePartDefs.h"
#include "controlobject.h"

Plane::Plane(QObject* parent)
    : QObject(parent)
{
    mVelocity = 0;
    mAccel = 0;
    mAltitude = 0;
    mLongitude = 0;
    mLatitude = 0;

    // adding basic control surfaces
    ControlObject* aileron_l = new ControlObject();
    ControlObject* aileron_r = new ControlObject();
    ControlObject* elevator_l = new ControlObject();
    ControlObject* elevator_r = new ControlObject();
    ControlObject* rudder = new ControlObject();
    ControlObject* fan = new ControlObject();

    aileron_l->setId(AILERON_LEFT);
    aileron_r->setId(AILERON_RIGHT);
    elevator_l->setId(ELEVATOR_LEFT);
    elevator_r->setId(ELEVATOR_RIGHT);
    rudder->setId(RUDDER);
    fan->setId(FAN);

    aileron_l->setType(ControlObject::BASIC_CTRL);
    aileron_r->setType(ControlObject::BASIC_CTRL);
    elevator_l->setType(ControlObject::BASIC_CTRL);
    elevator_r->setType(ControlObject::BASIC_CTRL);
    rudder->setType(ControlObject::BASIC_CTRL);
    fan->setType(ControlObject::BASIC_CTRL);

    addControlObject(aileron_l);
    addControlObject(aileron_r);
    addControlObject(elevator_l);
    addControlObject(elevator_r);
    addControlObject(rudder);
    addControlObject(fan);
}

Plane::~Plane()
{
    qDeleteAll(mSensorMap.values());
    qDeleteAll(mActuatorMap.values());
    qDeleteAll(mControlObjectMap.values());
}

void Plane::setOrientation(PlaneOrientation orientation)
{
    mOrientation = orientation;
}

IPlane::PlaneOrientation Plane::getOrientation()
{
    return mOrientation;
}

void Plane::setPosition(QVector3D position)
{
    mPosition = position;
}

QVector3D Plane::getPosition()
{
    return mPosition;
}

void Plane::setVelocity(double velocity)
{
    mVelocity = velocity;
}

double Plane::getVelocity()
{
    return mVelocity;
}

void Plane::setAcceleration(double accel)
{
    mAccel = accel;
}

double Plane::getAcceleration()
{
    return mAccel;
}

void Plane::setAltitude(double altitude)
{
    mAltitude = altitude;
}

double Plane::getAltitude()
{
    return mAltitude;
}

void Plane::setLatitude(double latitude)
{
    mLatitude = latitude;
}

double Plane::getLatitude()
{
    return mLatitude;
}

void Plane::setLongitude(double longitude)
{
    mLongitude = longitude;
}

double Plane::getLongitude()
{
    return mLongitude;
}

void Plane::addSensor(ISensor* sensor)
{
    int id = sensor->getId();
    ISensor* curSensor = getSensor(id);         // deleting current
    if(curSensor)
        delete curSensor;

    mSensorMap.insert(id,sensor);
}

void Plane::removeSensor(int id)
{
    ISensor* curSensor = getSensor(id);         // deleting current
    if(curSensor)
        delete curSensor;
    mSensorMap.remove(id);
}

ISensor* Plane::getSensor(int id)
{
    return mSensorMap.value(id,0);
}

void Plane::addActuator(IActuator* actuator)
{
    int id = actuator->getId();
    IActuator* curActuator = getActuator(id);         // deleting current
    if(curActuator)
        delete curActuator;

    mActuatorMap.insert(id,actuator);
}

void Plane::removeActuator(int id)
{
    IActuator* curActuator = getActuator(id);         // deleting current
    if(curActuator)
        delete curActuator;

    mActuatorMap.remove(id);
}

IActuator* Plane::getActuator(int id)
{
    return mActuatorMap.value(id,0);
}

void Plane::addControlObject(IControlObject* controlobj)
{
    int id = controlobj->getId();
    IControlObject* curControlObj = getControlObject(id);
    if(curControlObj)
        delete curControlObj;

    mControlObjectMap.insert(id,controlobj);
}

void Plane::removeControlObject(int id)
{
    IControlObject* curControlObj = getControlObject(id);
    if(curControlObj)
        delete curControlObj;

    mControlObjectMap.remove(id);
}

IControlObject* Plane::getControlObject(int id)
{
    return mControlObjectMap.value(id,0);
}
