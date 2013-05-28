#include "DataPackets_E.h"
#include "IControllerPipe.h"
#include "IBuffer_E.h"
#include "_String.h"

PacketFactory_E::PacketFactory_E()
{

}

PacketFactory_E::~PacketFactory_E()
{

}

IDataPacket_E* PacketFactory_E::createPacket(_CommPacketType type)
{
          IDataPacket_E* packet=0;
          switch(type)
          {
          case PACKET_CHECK_CONNECTION:
                    packet = new Packet_CheckConnection();
                    break;
          case PACKET_CHECK_CONNECTION_REPLY:
                    packet = new Packet_ConnReply();
                    break;
          case PACKET_REQUEST:
                    packet = new Packet_PacketRequest();
                    break;
          case PACKET_RESEND_REQUEST:
                    packet = new Packet_PacketResendRequest();
                    break;
          case PACKET_MODECHANGE_CMD:
                    packet = new Packet_ModeChangeCmd();
                    break;
          case PACKET_COMMAND:
                    packet = new Packet_Command();
                    break;
          case PACKET_LOCATION:
                    packet = new Packet_Location();
                    break;
          case PACKET_PATH:
                    packet = new Packet_Path();
                    break;
          case PACKET_HEALTH:
                    packet = new Packet_Helth();
                    break;
          case PACKET_DATA:
                    packet = new Packet_Data();
          case PACKET_HUMAN_CONTROL:
                    packet = new Packet_HumanControl();
                    break;
          case PACKET_DEBUG_INFO:
                    packet = new Packet_DebugInfo();
                    break;
          };
          return packet;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

Packet_CheckConnection::Packet_CheckConnection()
{

}

Packet_CheckConnection::~Packet_CheckConnection()
{

}

_CommPacketType Packet_CheckConnection::type()
{
          return PACKET_CHECK_CONNECTION;
}

void Packet_CheckConnection::_sendSerial(IControllerPipe* pipe)
{
          // packet type itself holds information
}

bool Packet_CheckConnection::_readSerial(IBuffer_E* buffer)
{
          return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

Packet_ConnReply::Packet_ConnReply()
{
         mStatus = CONNECTION_OK;
}

Packet_ConnReply::~Packet_ConnReply()
{

}

_CommPacketType Packet_ConnReply::type()
{
          return PACKET_CHECK_CONNECTION_REPLY;
}

void Packet_ConnReply::_sendSerial(IControllerPipe* pipe)
{
          pipe->_serialWrite((_BYTE)mStatus);
}

bool Packet_ConnReply::_readSerial(IBuffer_E* buffer)
{
          bool bSucces = false;
          if(!buffer->isEmpty())
          {
                    mStatus = (_CommConnectionStatus)buffer->readByte();
                    bSucces = true;
          }
          return bSucces;
}

void Packet_ConnReply::setConnectionStatus(_CommConnectionStatus status)
{
          mStatus = status;
}

_CommConnectionStatus Packet_ConnReply::getConnectionStatus()
{
          return mStatus;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

Packet_PacketRequest::Packet_PacketRequest()
{
          mReqType = PACKET_DATA;
}

Packet_PacketRequest::~Packet_PacketRequest()
{

}

_CommPacketType Packet_PacketRequest::type()
{
          return PACKET_REQUEST;
}

void Packet_PacketRequest::_sendSerial(IControllerPipe* pipe)
{
          pipe->_serialWrite((_BYTE)mReqType);
}

bool Packet_PacketRequest::_readSerial(IBuffer_E* buffer)
{
          bool bSucces = false;
          if(!buffer->isEmpty())
          {
                    mReqType = (_CommPacketType)buffer->readByte();
                    bSucces = true;
          }
          return bSucces;
}

 void Packet_PacketRequest::setReqType(_CommPacketType type)
 {
          mReqType = type;
 }

_CommPacketType Packet_PacketRequest::reqType()
{
          return mReqType;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////

Packet_PacketResendRequest::Packet_PacketResendRequest()
{
          mReqType = PACKET_DATA;
          mReqId = 0;
}

Packet_PacketResendRequest::~Packet_PacketResendRequest()
{

}

_CommPacketType Packet_PacketResendRequest::type()
{
          return PACKET_RESEND_REQUEST;
}

void Packet_PacketResendRequest::_sendSerial(IControllerPipe* pipe)
{
          pipe->_serialWrite((_BYTE)mReqType);
          pipe->_serialWrite(mReqId);
}

bool Packet_PacketResendRequest::_readSerial(IBuffer_E* buffer)
{
          bool bSucces = false;
          if(!buffer->isEmpty())
          {
                    mReqType = (_CommPacketType)buffer->readByte();
                    mReqId = (_BYTE)buffer->readByte();
                    bSucces = true;
          }
          return bSucces;
}

 void Packet_PacketResendRequest::setReqType(_CommPacketType type)
 {
          mReqType = type;
 }

_CommPacketType Packet_PacketResendRequest::reqType()
{
          return mReqType;
}
void Packet_PacketResendRequest::setReqId(_BYTE id)
{
          mReqId = id;
}

_BYTE Packet_PacketResendRequest::getReqId()
{
          return mReqId;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

Packet_ModeChangeCmd::Packet_ModeChangeCmd()
{
          mMode = FLY_AUTONOMOUS;
}

Packet_ModeChangeCmd::~Packet_ModeChangeCmd()
{

}

_CommPacketType Packet_ModeChangeCmd::type()
{
          return PACKET_MODECHANGE_CMD;
}

void Packet_ModeChangeCmd::_sendSerial(IControllerPipe* pipe)
{
          pipe->_serialWrite((_BYTE)mMode);
}

bool Packet_ModeChangeCmd::_readSerial(IBuffer_E* buffer)
{
          bool bSucces = false;
          if(!buffer->isEmpty())
          {
                    mMode = (_PlaneFlyMode)buffer->readByte();
                    bSucces = true;
          }
          return bSucces;
}

 void Packet_ModeChangeCmd::setMode(_PlaneFlyMode mode)
 {
           mMode =  mode;
 }

_PlaneFlyMode Packet_ModeChangeCmd::getMode()
{
          return mMode;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

Packet_Command::Packet_Command()
{
          mId = 0;
}

Packet_Command::~Packet_Command()
{

}

_CommPacketType Packet_Command::type()
{
          return PACKET_COMMAND;
}

void Packet_Command::_sendSerial(IControllerPipe* pipe)
{
          pipe->_serialWrite(mId);
          // send further command data
}

bool Packet_Command::_readSerial(IBuffer_E* buffer)
{
          bool bSucces = false;
          if(!buffer->isEmpty())
          {
                    mId = (_BYTE)buffer->readByte();
                    // read further command data

                    bSucces = true;
          }
          return bSucces;
}

void Packet_Command::setCommandId(_BYTE id)
{
          mId = id;
}

_BYTE Packet_Command::getCommandId()
{
          return mId;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

Packet_Location::Packet_Location()
{
          mPitch = 0;
          mRoll = 0;
          mYaw = 0;
          bCheckSumMatched = false;
}

Packet_Location::~Packet_Location()
{

}

_CommPacketType Packet_Location::type()
{
          return PACKET_LOCATION;
}

void Packet_Location::_sendSerial(IControllerPipe* pipe)
{
          const int sizeofFloat = sizeof(float);
          const int len = 6*2*sizeofFloat;
          _BYTE data[len];
          float altitude = mPos.altitude;
          float latitude = mPos.latitude;
          float longitude = mPos.longitude;

          _BYTE* dataPtr = _String::packInString(data,(_BYTE*)&altitude,sizeofFloat);
          dataPtr = _String::packInString(dataPtr,(_BYTE*)&latitude,sizeofFloat);
          dataPtr = _String::packInString(dataPtr,(_BYTE*)&longitude,sizeofFloat);

          dataPtr = _String::packInString(dataPtr,(_BYTE*)&mPitch,sizeofFloat);
          dataPtr = _String::packInString(dataPtr,(_BYTE*)&mRoll,sizeofFloat);
          dataPtr = _String::packInString(dataPtr,(_BYTE*)&mYaw,sizeofFloat);

          _BYTE checkSome=0x00;
          for(int i=0; i<len; i++)
          {
                    pipe->_serialWrite(data[i]);
                    checkSome = checkSome ^ data[i];
          }
          pipe->_serialWrite(checkSome);
}

bool Packet_Location::_readSerial(IBuffer_E* buffer)
{
          bCheckSumMatched = false;
          const int sizeofFloat = sizeof(float);
          const int len = 6*2*sizeofFloat;

          if(buffer->count() > len)   // len + checksum
          {
                    _BYTE data[len];
                    _BYTE checkSome=0x00;
                    for(int i=0; i<len; i++)
                    {
                              data[i] = (_BYTE)(buffer->readByte());
                              checkSome = checkSome ^ data[i];
                    }
                    float altitude = mPos.altitude;
                    float latitude = mPos.latitude;
                    float longitude = mPos.longitude;
                    _BYTE* dataPtr = _String::unpackString(data,(_BYTE*)&altitude,sizeofFloat);
                    dataPtr = _String::unpackString(dataPtr,(_BYTE*)&latitude,sizeofFloat);
                    dataPtr = _String::unpackString(dataPtr,(_BYTE*)&longitude,sizeofFloat);

                    mPos.altitude = altitude;
                    mPos.latitude = latitude;
                    mPos.longitude = longitude;

                    dataPtr = _String::unpackString(dataPtr,(_BYTE*)&mPitch,sizeofFloat);
                    dataPtr = _String::unpackString(dataPtr,(_BYTE*)&mRoll,sizeofFloat);
                    dataPtr = _String::unpackString(dataPtr,(_BYTE*)&mYaw,sizeofFloat);

                    _BYTE reqCheckSum   =  (_BYTE)(buffer->readByte());                                           // check sum matches
                    if(reqCheckSum == checkSome)
                    {
                              bCheckSumMatched = true;
                    }
          }
          return bCheckSumMatched;
}

void Packet_Location::setPos(const _GPSPosition& pos)
{
          mPos = pos;
}

_GPSPosition Packet_Location::getPos()
{
          return mPos;
}

void Packet_Location::setOrientation(float pitch,float roll,float yaw)
{
          mPitch = pitch;
          mRoll = roll;
          mYaw = yaw;
}

float Packet_Location::getPitch()
{
          return mPitch;
}

float Packet_Location::getRoll()
{
          return mRoll;
}

float Packet_Location::getYaw()
{
          return mYaw;
}

bool Packet_Location::hasCheckSumMatched()
{
          return bCheckSumMatched;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////

Packet_Path::Packet_Path()
{

}

Packet_Path::~Packet_Path()
{

}

_CommPacketType Packet_Path::type()
{
          return PACKET_PATH;
}

void Packet_Path::_sendSerial(IControllerPipe* pipe)
{

}

bool Packet_Path::_readSerial(IBuffer_E* buffer)
{
          return true;
}

void Packet_Path::setPath(const _LinkedList<_GPSPosition>&  posList)
{
          mPosList = posList;
}

_LinkedList<_GPSPosition> Packet_Path::getPath()
{
          return mPosList;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////

Packet_Helth::Packet_Helth()
{

}

Packet_Helth::~Packet_Helth()
{

}

_CommPacketType Packet_Helth::type()
{
          return PACKET_HEALTH;
}

void Packet_Helth::_sendSerial(IControllerPipe* pipe)
{

}

bool Packet_Helth::_readSerial(IBuffer_E* buffer)
{
          return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////

Packet_Data::Packet_Data()
{

}

Packet_Data::~Packet_Data()
{

}

_CommPacketType Packet_Data::type()
{
          return PACKET_DATA;
}

void Packet_Data::_sendSerial(IControllerPipe* pipe)
{

}

bool Packet_Data::_readSerial(IBuffer_E* buffer)
{
          return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

Packet_HumanControl::Packet_HumanControl()
{
          mAileronAngle = 0;
          mElevatorAngle = 0;
          mRudderAngle = 0;
          mThrust = 0;
}

Packet_HumanControl::~Packet_HumanControl()
{

}

_CommPacketType Packet_HumanControl::type()
{
          return PACKET_HUMAN_CONTROL;
}

void Packet_HumanControl::_sendSerial(IControllerPipe* pipe)
{

}

bool Packet_HumanControl::_readSerial(IBuffer_E* buffer)
{

}

 void Packet_HumanControl::setAileronAngle(float angle)
 {
          mAileronAngle = angle;
 }

 float Packet_HumanControl::getAileronAngle()
 {
          return mAileronAngle;
 }

void Packet_HumanControl::setElevatorAngle(float angle)
{
          mElevatorAngle = angle;
}

float Packet_HumanControl::getElevatorAngle()
{
          return mElevatorAngle;
}

void Packet_HumanControl::setRudderAngle(float angle)
{
          mRudderAngle = angle;
}

float Packet_HumanControl::getRudderAngle()
{
          return mRudderAngle;
}

void Packet_HumanControl::setThrust(float thrust)
{
          mThrust = thrust;
}

float Packet_HumanControl::getThrust()
{
          return mThrust;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

Packet_DebugInfo::Packet_DebugInfo()
{

}

Packet_DebugInfo::~Packet_DebugInfo()
{

}

_CommPacketType Packet_DebugInfo::type()
{
          return PACKET_DEBUG_INFO;
}

void Packet_DebugInfo::_sendSerial(IControllerPipe* pipe)
{

}

bool Packet_DebugInfo::_readSerial(IBuffer_E* buffer)
{
          return true;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
