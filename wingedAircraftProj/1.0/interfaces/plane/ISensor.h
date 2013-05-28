#ifndef ISENSOR_H
#define ISENSOR_H

#include <QVariant>

class ISensor
{
public:
    enum SensorType
    {
        UNKNOWN_TYPE = -1
    };

    virtual ~ISensor() {}
    virtual void setValue(QVariant value)=0;
    virtual QVariant getValue()=0;
    virtual void setId(int id)=0;
    virtual int getId()=0;
    virtual SensorType getType()=0;
};

#endif // ISENSOR_H
