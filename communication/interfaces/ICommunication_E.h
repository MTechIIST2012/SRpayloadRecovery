#ifndef ICOMMUNICATION_E_H_INCLUDED
#define ICOMMUNICATION_E_H_INCLUDED

#include "embedded_typedefs.h"

class IDataPacket_E;
class IPacketFactory_E;
class IControllerPipe;
class IBuffer_E;

class ICommunication_E
{
public:
          virtual ~ICommunication_E() {}
          virtual void start(int baud)=0;
          virtual void stop()=0;
          virtual void setControllerPipe(IControllerPipe* pipe)=0;
          virtual IControllerPipe* getControllerPipe()=0;
          virtual void setFactory(IPacketFactory_E* factory)=0;
          virtual IPacketFactory_E* getFactory()=0;
          virtual _CommConnectionStatus checkConnection()=0;
          virtual void sendPacket(IDataPacket_E* packet)=0;
          virtual IDataPacket_E* readPacket()=0;
          virtual void updateBuffer()=0;
};

class IPacketFactory_E
{
public:
          virtual ~IPacketFactory_E() {}
          virtual IDataPacket_E* createPacket(_CommPacketType type)=0;
};

class IDataPacket_E
{
public:
          virtual ~IDataPacket_E() {}
          virtual _CommPacketType type()=0;
          virtual void _sendSerial(IControllerPipe* pipe)=0;
          virtual bool _readSerial(IBuffer_E* buffer)=0;
};



#endif // ICOMMUNICATION_E_H_INCLUDED
