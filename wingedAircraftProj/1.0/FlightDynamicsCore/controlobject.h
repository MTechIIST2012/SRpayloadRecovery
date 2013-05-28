#ifndef CONTROLOBJECT_H
#define CONTROLOBJECT_H

#include "IControlObject.h"
#include "FlightDynamicsCore_global.h"

class FLIGHTDYNAMICSCORESHARED_EXPORT ControlObject : public IControlObject
{
public:
    ControlObject();
    virtual ~ControlObject();
    virtual void setValue(QVariant value);
    virtual QVariant getValue();
    virtual void setId(int id);
    virtual int getId();
    virtual void setType(ControlObjectType type);
    virtual ControlObjectType getType();
private:
    ControlObjectType mControlObjType;
    int mId;
    QVariant mValue;
};

#endif // CONTROLOBJECT_H
