#ifndef ICONTROLLEDOBJ_E_H_INCLUDED
#define ICONTROLLEDOBJ_E_H_INCLUDED

#include "planepartdefs.h"

class IControlledObj_E
{
public:
          virtual ~IControlledObj_E() {}
          virtual ControlledObjID_E getId()=0;
          virtual bool complete()=0;
          virtual void cancelOperation()=0;
};

#endif // ICONTROLLEDOBJ_E_H_INCLUDED
