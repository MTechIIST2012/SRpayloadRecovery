#ifndef IPLANECONTROLLER_H_INCLUDED
#define IPLANECONTROLLER_H_INCLUDED

#include "IControllerPipe.h"

class IPlane_E;
class ICommunication_E;

class IPlaneController
{
    public:
            virtual ~IPlaneController()  {}
            //virtual  void setControllerPipe(IControllerPipe* pipe)=0;
            virtual  IControllerPipe*  getControllerPipe()=0;
            //virtual void setPlane(IPlane_E* plane)=0;
            virtual IPlane_E* getPlane()=0;
            //virtual void setCommunication(ICommunication_E* comm)=0;
            virtual ICommunication_E* getCommunication()=0;
            virtual  void  setup()=0;
            virtual  void  loop()=0;
};



#endif // IPLANECONTROLLER_H_INCLUDED
