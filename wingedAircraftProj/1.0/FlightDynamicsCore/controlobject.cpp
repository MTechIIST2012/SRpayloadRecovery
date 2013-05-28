#include "controlobject.h"

ControlObject::ControlObject()
{
    mControlObjType = IControlObject::UNKNOWN_TYPE;
    mValue = 0;
}

ControlObject::~ControlObject()
{

}

void ControlObject::setValue(QVariant value)
{
    mValue = value;
}

QVariant ControlObject::getValue()
{
    return mValue;
}

void ControlObject::setId(int id)
{
    mId = id;
}

int ControlObject::getId()
{
    return mId;
}

void ControlObject::setType(ControlObjectType type)
{
    mControlObjType = type;
}

IControlObject::ControlObjectType ControlObject::getType()
{
    return mControlObjType;
}
