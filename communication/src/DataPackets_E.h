#ifndef DATAPACKETS_E_H
#define DATAPACKETS_E_H

#include "ICommunication_E.h"
#include "_LinkedList.h"

// packet factory
class PacketFactory_E : public IPacketFactory_E
{
public:
          PacketFactory_E();
          virtual ~PacketFactory_E();
          virtual IDataPacket_E* createPacket(_CommPacketType type);
};

// packets

class Packet_CheckConnection : public IDataPacket_E
{
public:
          Packet_CheckConnection();
          virtual ~Packet_CheckConnection();
          virtual _CommPacketType type();
          virtual void _sendSerial(IControllerPipe* pipe);
          virtual bool _readSerial(IBuffer_E* buffer);
};

class Packet_ConnReply : public IDataPacket_E
{
public:
          Packet_ConnReply();
          virtual ~Packet_ConnReply();
          virtual _CommPacketType type();
          virtual void _sendSerial(IControllerPipe* pipe);
          virtual bool _readSerial(IBuffer_E* buffer);

          void setConnectionStatus(_CommConnectionStatus status);
          _CommConnectionStatus getConnectionStatus();
private:
          _CommConnectionStatus mStatus;
};

class Packet_PacketRequest : public IDataPacket_E
{
public:
          Packet_PacketRequest();
          virtual ~Packet_PacketRequest();
          virtual _CommPacketType type();
          virtual void _sendSerial(IControllerPipe* pipe);
          virtual bool _readSerial(IBuffer_E* buffer);

          void setReqType(_CommPacketType type);
          _CommPacketType reqType();
private:
          _CommPacketType mReqType;
};

class Packet_PacketResendRequest : public IDataPacket_E
{
public:
          Packet_PacketResendRequest();
          virtual ~Packet_PacketResendRequest();
          virtual _CommPacketType type();
          virtual void _sendSerial(IControllerPipe* pipe);
          virtual bool _readSerial(IBuffer_E* buffer);

          void setReqType(_CommPacketType type);
          _CommPacketType reqType();
          void setReqId(_BYTE id);
          _BYTE getReqId();
private:
          _CommPacketType mReqType;
          _BYTE mReqId;
};

class Packet_ModeChangeCmd : public IDataPacket_E
{
public:
          Packet_ModeChangeCmd();
          virtual ~Packet_ModeChangeCmd();
          virtual _CommPacketType type();
          virtual void _sendSerial(IControllerPipe* pipe);
          virtual bool _readSerial(IBuffer_E* buffer);

          void setMode(_PlaneFlyMode mode);
          _PlaneFlyMode getMode();
private:
          _PlaneFlyMode mMode;
};

class Packet_Command : public IDataPacket_E
{
public:
          Packet_Command();
          virtual ~Packet_Command();
          virtual _CommPacketType type();
          virtual void _sendSerial(IControllerPipe* pipe);
          virtual bool _readSerial(IBuffer_E* buffer);

          void setCommandId(_BYTE id);
          _BYTE getCommandId();
private:
          _BYTE mId;
};

class Packet_Location : public IDataPacket_E
{
public:
          Packet_Location();
          virtual ~Packet_Location();
          virtual _CommPacketType type();
          virtual void _sendSerial(IControllerPipe* pipe);
          virtual bool _readSerial(IBuffer_E* buffer);

          void setPos(const _GPSPosition& pos);
          _GPSPosition getPos();
          void setOrientation(float pitch,float roll,float yaw);
          float getPitch();
          float getRoll();
          float getYaw();
          bool hasCheckSumMatched();
private:
          _GPSPosition mPos;
          float mPitch;
          float mRoll;
          float mYaw;
          bool bCheckSumMatched;
};

class Packet_Path : public IDataPacket_E
{
public:
          Packet_Path();
          virtual ~Packet_Path();
          virtual _CommPacketType type();
          virtual void _sendSerial(IControllerPipe* pipe);
          virtual bool _readSerial(IBuffer_E* buffer);

          void setPath(const _LinkedList<_GPSPosition>&  posList);
          _LinkedList<_GPSPosition> getPath();
private:
          _LinkedList<_GPSPosition> mPosList;
};

class Packet_Helth : public IDataPacket_E
{
public:
          Packet_Helth();
          virtual ~Packet_Helth();
          virtual _CommPacketType type();
          virtual void _sendSerial(IControllerPipe* pipe);
          virtual bool _readSerial(IBuffer_E* buffer);
};

class Packet_Data : public IDataPacket_E
{
public:
          Packet_Data();
          virtual ~Packet_Data();
          virtual _CommPacketType type();
          virtual void _sendSerial(IControllerPipe* pipe);
          virtual bool _readSerial(IBuffer_E* buffer);
};

class Packet_HumanControl : public IDataPacket_E
{
public:
          Packet_HumanControl();
          virtual ~Packet_HumanControl();
          virtual _CommPacketType type();
          virtual void _sendSerial(IControllerPipe* pipe);
          virtual bool _readSerial(IBuffer_E* buffer);

          void setAileronAngle(float angle);
          float getAileronAngle();
          void setElevatorAngle(float angle);
          float getElevatorAngle();
          void setRudderAngle(float angle);
          float getRudderAngle();
          void setThrust(float thrust);
          float getThrust();
private:
          float mAileronAngle;
          float mElevatorAngle;
          float mRudderAngle;
          float mThrust;
};

class Packet_DebugInfo : public IDataPacket_E
{
public:
          Packet_DebugInfo();
          virtual ~Packet_DebugInfo();
          virtual _CommPacketType type();
          virtual void _sendSerial(IControllerPipe* pipe);
          virtual bool _readSerial(IBuffer_E* buffer);
};

#endif // DATAPACKETS_E_H
