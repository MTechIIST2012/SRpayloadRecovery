#ifndef EMBEDDED_TYPEDEFS_H_INCLUDED
#define EMBEDDED_TYPEDEFS_H_INCLUDED

typedef unsigned char _BYTE;
typedef unsigned char INT_8;

#define   _HIGH   0x1
#define   _LOW    0x0

#define    _INPUT       0x0
#define   _OUTPUT       0x1

struct _GPSPosition
{
          double latitude;
          double longitude;
          double altitude;

          _GPSPosition(double latit=0,double longi=0,double altitu=0)
          {
                    latitude = latit;
                    longitude = longi;
                    altitude = altitu;
          }
};


enum  _PlaneState
{
          PLANE_OFF,
          PLANE_TAKING_OFF,
          PLANE_FLYING,
          PLANE_LANDING
};

enum _PlaneFlyMode
{
          FLY_AUTONOMOUS,
          FLY_IN_CIRCLE,
          FLY_HUMANCONTROL
};

//      Data packet related.

#define  START_OF_PACKET   0xFF
#define  END_OF_PACKET   0xFE
#define COMM_VALUE_SAPORTATOR  ','

enum _CommConnectionStatus
{
          CONNECTION_FAILED,
          CONNECTION_BUSY,
          CONNECTION_OK
};


enum _CommPacketType
{
          PACKET_CHECK_CONNECTION,
          PACKET_CHECK_CONNECTION_REPLY,
          PACKET_REQUEST,
          PACKET_RESEND_REQUEST,
          PACKET_MODECHANGE_CMD,
          PACKET_COMMAND,
          PACKET_LOCATION,
          PACKET_PATH,
          PACKET_HEALTH,
          PACKET_DATA,
          PACKET_HUMAN_CONTROL,
          PACKET_DEBUG_INFO,
};


#endif // EMBEDDED_TYPEDEFS_H_INCLUDED
