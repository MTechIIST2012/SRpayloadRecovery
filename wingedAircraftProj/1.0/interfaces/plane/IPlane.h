#ifndef IPLANE_H
#define IPLANE_H

#include <QVector3D>

#include "ISensor.h"
#include "IActuator.h"
#include "IControlObject.h"

class IPlane
{
public:
    struct PlaneOrientation
    {
        double pitch;
        double roll;
        double yaw;

        PlaneOrientation()
        {
            pitch = 0;
            roll = 0;
            yaw = 0;
        }
    };


    virtual ~IPlane() {}

    virtual void setOrientation(PlaneOrientation orientation)=0;
    virtual PlaneOrientation getOrientation()=0;
    virtual void setPosition(QVector3D position)=0;
    virtual QVector3D getPosition()=0;
    virtual void setVelocity(double velocity)=0;
    virtual double getVelocity()=0;
    virtual void setAcceleration(double accel)=0;
    virtual double getAcceleration()=0;

    virtual void setAltitude(double altitude)=0;
    virtual double getAltitude()=0;
    virtual void setLatitude(double latitude)=0;
    virtual double getLatitude()=0;
    virtual void setLongitude(double longitude)=0;
    virtual double getLongitude()=0;

    virtual void addSensor(ISensor* sensor)=0;
    virtual void removeSensor(int id)=0;
    virtual ISensor* getSensor(int id)=0;

    virtual void addActuator(IActuator* actuator)=0;
    virtual void removeActuator(int id)=0;
    virtual IActuator* getActuator(int id)=0;

    virtual void addControlObject(IControlObject* controlobj)=0;
    virtual void removeControlObject(int id)=0;
    virtual IControlObject* getControlObject(int id)=0;
};

#endif // IPLANE_H
