#ifndef PLANE_H
#define PLANE_H

#include <QObject>
#include <QHash>
#include "IPlane.h"
#include "FlightDynamicsCore_global.h"

class FLIGHTDYNAMICSCORESHARED_EXPORT Plane : public QObject, public IPlane
{
    Q_OBJECT
public:
    Plane(QObject* parent=0);
    virtual ~Plane();
    virtual void setOrientation(PlaneOrientation orientation);
    virtual PlaneOrientation getOrientation();
    virtual void setPosition(QVector3D position);
    virtual QVector3D getPosition();
    virtual void setVelocity(double velocity);
    virtual double getVelocity();
    virtual void setAcceleration(double accel);
    virtual double getAcceleration();

    virtual void setAltitude(double altitude);
    virtual double getAltitude();
    virtual void setLatitude(double latitude);
    virtual double getLatitude();
    virtual void setLongitude(double longitude);
    virtual double getLongitude();

    virtual void addSensor(ISensor* sensor);
    virtual void removeSensor(int id);
    virtual ISensor* getSensor(int id);

    virtual void addActuator(IActuator* actuator);
    virtual void removeActuator(int id);
    virtual IActuator* getActuator(int id);

    virtual void addControlObject(IControlObject* controlobj);
    virtual void removeControlObject(int id);
    virtual IControlObject* getControlObject(int id);
private:
    double mVelocity;
    double mAccel;
    double mAltitude;
    double mLongitude;
    double mLatitude;
    QVector3D mPosition;
    PlaneOrientation mOrientation;
    QHash<int,ISensor*> mSensorMap;
    QHash<int,IActuator*> mActuatorMap;
    QHash<int,IControlObject*> mControlObjectMap;
};

#endif // PLANE_H
