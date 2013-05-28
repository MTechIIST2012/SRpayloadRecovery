#ifndef COMMUNICATION_E_H
#define COMMUNICATION_E_H

#include "ICommunication_E.h"

class IBuffer_E;

class Communication_E : public ICommunication_E
{
public:
          Communication_E(IPacketFactory_E* factory,IControllerPipe* cPipe,unsigned int bufferSize=100);
          virtual ~Communication_E();
          virtual void start(int baud);
          virtual void stop();
          virtual void setControllerPipe(IControllerPipe* pipe);
          virtual IControllerPipe* getControllerPipe();
          virtual void setFactory(IPacketFactory_E* factory);
          virtual IPacketFactory_E* getFactory();
          virtual _CommConnectionStatus checkConnection();
          virtual void sendPacket(IDataPacket_E* packet);
          virtual IDataPacket_E* readPacket();
          virtual void updateBuffer();
private:
          IControllerPipe* mPipe;
          IPacketFactory_E* mPacketFactory;
          IBuffer_E* mDataBuffer;
};

#endif // COMMUNICATION_E_H
