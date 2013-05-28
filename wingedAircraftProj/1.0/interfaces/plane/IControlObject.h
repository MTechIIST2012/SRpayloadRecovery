#ifndef ICONTROLOBJECT_H
#define ICONTROLOBJECT_H

#include <QVariant>

class IControlObject
{
public:
    enum ControlObjectType
    {
        UNKNOWN_TYPE = -1,
        BASIC_CTRL
    };

    virtual ~IControlObject() {}
    virtual void setValue(QVariant value)=0;
    virtual QVariant getValue()=0;
    virtual void setId(int id)=0;
    virtual int getId()=0;
    virtual void setType(ControlObjectType type)=0;
    virtual ControlObjectType getType()=0;
};

#endif // ICONTROLOBJECT_H
