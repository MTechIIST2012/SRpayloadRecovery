#ifndef PLANECONTROLLER_H
#define PLANECONTROLLER_H

#include "IPlaneController.h"

//  PlaneController  is a singleton class.
class PlaneController         :         public IPlaneController
{
public:
          static void  generateInstance(IPlane_E* plane,IControllerPipe* pipe,ICommunication_E* comm);
          static IPlaneController*  instance();

          virtual ~PlaneController();
          virtual  IControllerPipe*  getControllerPipe();
          virtual IPlane_E* getPlane();
          virtual ICommunication_E* getCommunication();
          virtual  void  setup();
          virtual  void  loop();
private:
          PlaneController(IPlane_E* plane,IControllerPipe* pipe,ICommunication_E* comm);
          virtual void setPlane(IPlane_E* plane);
          virtual  void setControllerPipe(IControllerPipe* pipe);
          virtual void setCommunication(ICommunication_E* comm);

         static IPlaneController* mSelf;
         IControllerPipe* mPipe;
         IPlane_E* mPlane;
         ICommunication_E* mComm;
};

#endif // PLANECONTROLLER_H
