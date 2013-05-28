#include "PlaneController.h"
#include "IPlane_E.h"
#include "ICommunication_E.h"
#include "IGPS_E.h"
#include "IGyroMeter_E.h"
#include "DataPackets_E.h"

IPlaneController* PlaneController::mSelf=0;

void  PlaneController::generateInstance(IPlane_E* plane,IControllerPipe* pipe,ICommunication_E* comm)
{
          if(mSelf==0)
                    mSelf = new PlaneController(plane,pipe,comm);
}

IPlaneController*  PlaneController::instance()
{
          return mSelf;
}

PlaneController::~PlaneController()
{
          delete mPipe;
}

IControllerPipe*  PlaneController::getControllerPipe()
{
          return mPipe;
}

IPlane_E* PlaneController::getPlane()
{
          return mPlane;
}

ICommunication_E* PlaneController::getCommunication()
{
          return mComm;
}

void onTimer1TimeOut()
{
          IPlaneController* controller = PlaneController::instance();
          if(controller)
          {
                    ICommunication_E* comm = controller->getCommunication();
                    if(comm)
                    {
                              comm->updateBuffer();
                    }
          }
}

//  the setup function.
void  PlaneController::setup()
{
          IControllerPipe*  cPipe = getControllerPipe();
          cPipe->_pinMode(13,_OUTPUT);
          cPipe->_digitalWrite(13,_HIGH);
          cPipe->_serialBegin(9600);
          cPipe->_timer1_initialize(5000);
          cPipe->_timer1_attachInterrupt(onTimer1TimeOut);
           //cPipe->_serialPrintln("Starting engine");
          //mPlane->startEngine();


}

// the loop function.
void  PlaneController::loop()
{

          IControllerPipe*  cPipe = getControllerPipe();
//          cPipe->_serialPrintln("Loop start");
//          cPipe->_serialPrintln("Please enter");
//
//          while(cPipe->_serialAvailable() == 0) ;

//           INT_8 curVal = (INT_8)(cPipe->_digitalRead(13));
//          INT_8  newVal = curVal ^ 0xff;
//          cPipe->_digitalWrite(13,newVal);

//          int data = cPipe->_serialRead();
//          cPipe->_serialPrint(data - '0');
//          cPipe->_serialPrintln("Loop complete");

          //cPipe->_serialPrintln("Flying");
          mPlane->fly();
          cPipe->_delay(1000);
          if(mComm->checkConnection())
          {
                    cPipe->_digitalWrite(13,_HIGH);
                    IGPS_E* gps = static_cast<IGPS_E*>(mPlane->getMeter(GPS_E));
                    IGyroMeter_E* gyro = static_cast<IGyroMeter_E*>(mPlane->getMeter(GYROMETER_E));
                    if(gps && gyro)
                    {
                              IPacketFactory_E* factory = mComm->getFactory();
                              IDataPacket_E* packet = factory->createPacket(PACKET_LOCATION);
                              Packet_Location* posPacket = static_cast<Packet_Location*>(packet);
                              if(posPacket)
                              {

                                        posPacket->setPos(_GPSPosition(gps->latitude(),gps->longitude(),gps->altitude()));
                                        posPacket->setOrientation(gyro->pitch(),gyro->roll(),gyro->yaw());
                                        mComm->sendPacket(posPacket);
                              }

                              if(packet)
                                delete packet;
                    }
          }
          else
          {
                    cPipe->_digitalWrite(13,_LOW);
          }
}

// private members.

PlaneController::PlaneController(IPlane_E* plane,IControllerPipe*   pipe,ICommunication_E* comm)
{
          setControllerPipe(pipe);
          setPlane(plane);
          setCommunication(comm);
}

void PlaneController::setPlane(IPlane_E* plane)
{
          mPlane = plane;
}

void PlaneController::setControllerPipe(IControllerPipe* pipe)
{
          mPipe =  pipe;
}

void PlaneController::setCommunication(ICommunication_E* comm)
{
          mComm = comm;
}
