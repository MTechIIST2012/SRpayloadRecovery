#include "Communication_E.h"
#include "IControllerPipe.h"
#include "_CircularBuffer.h"
#include "DataPackets_E.h"

Communication_E::Communication_E(IPacketFactory_E* factory,IControllerPipe* cPipe,unsigned int bufferSize)
{
          mPacketFactory = factory;
          mPipe = cPipe;
          mDataBuffer = new _CircularBuffer(bufferSize);
}

Communication_E::~Communication_E()
{
          if(mPacketFactory)
                    delete mPacketFactory;
          if(mPipe)
                    delete mPipe;

          delete mDataBuffer;
}

void  Communication_E::start(int baud)
{
          mPipe->_serialBegin(baud);
}

void  Communication_E::stop()                      // Todo: needs to be implimented.
{

}

void  Communication_E::setControllerPipe(IControllerPipe* pipe)
{
          mPipe = pipe;
}

IControllerPipe*  Communication_E::getControllerPipe()
{
          return mPipe;
}

void  Communication_E::setFactory(IPacketFactory_E* factory)
{
          mPacketFactory = factory;
}

IPacketFactory_E*  Communication_E::getFactory()
{
          return mPacketFactory;
}

_CommConnectionStatus  Communication_E::checkConnection()                                          // Todo: needs to be implimented.
{
          _CommConnectionStatus connStatus = CONNECTION_FAILED;
          IDataPacket_E* pktCheckConn = mPacketFactory->createPacket(PACKET_CHECK_CONNECTION);
          if(pktCheckConn)
          {
                    sendPacket(pktCheckConn);
                    mPipe->_delay(5);
                    IDataPacket_E* connReply = readPacket();
                    if(connReply)
                    {
                              connStatus = ((Packet_ConnReply*)connReply)->getConnectionStatus();
                              delete connReply;
                    }
                    delete pktCheckConn;
          }
          return connStatus;
}

void  Communication_E::sendPacket(IDataPacket_E* packet)          // Todo: needs to be implimented.
{
          mPipe->_serialWrite(START_OF_PACKET);
          mPipe->_serialWrite((_BYTE)packet->type());
          packet->_sendSerial(mPipe);
          mPipe->_serialWrite(END_OF_PACKET);
}

IDataPacket_E*  Communication_E::readPacket()
{
          IDataPacket_E*  packet = 0;
          if(mDataBuffer->contains(END_OF_PACKET))
          {
                    int DataCount = mDataBuffer->count();
                    bool bFound = false;
                    for(int i=0; i<DataCount; i++)
                    {
                              _BYTE byte = (_BYTE)(mDataBuffer->readByte());
                              if(byte == ((_BYTE)START_OF_PACKET))
                              {
                                        bFound = true;
                                        break;
                              }
                    }
                    if(bFound)
                    {
                              _BYTE type = mDataBuffer->readByte();
                              packet = mPacketFactory->createPacket((_CommPacketType)type);
                              if(packet)
                              {
                                        if(!packet->_readSerial(mDataBuffer))
                                        {
                                                  delete packet;
                                                  packet = 0;
                                        }
                              }
                    }
          }
          return  packet;
}

void Communication_E::updateBuffer()
{
          while(mPipe->_serialAvailable())
          {
                    _BYTE data = mPipe->_serialRead();
                    mDataBuffer->writeByte(data);
          }
}

