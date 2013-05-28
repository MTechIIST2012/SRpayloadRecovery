#ifndef IACTUATOR_H
#define IACTUATOR_H

#include <QVariant>

class IActuator
{
public:
    enum ActuatorType
    {
        UNKNOWN_TYPE = -1
    };

    virtual ~IActuator() {}
    virtual void setValue(QVariant value)=0;
    virtual QVariant getValue()=0;
    virtual void setId(int id)=0;
    virtual int getId()=0;
    virtual ActuatorType getType()=0;
};

#endif // IACTUATOR_H
