#ifndef IENGINE_E_H_INCLUDED
#define IENGINE_E_H_INCLUDED

#include "IControlledObj_E.h"

class IEngine_E : public IControlledObj_E
{
public:
          virtual ~IEngine_E() {}
          virtual void start()=0;
          virtual void stop()=0;
          virtual bool isOn()=0;
};

#endif // IENGINE_E_H_INCLUDED
