#ifndef ICONTROLLERPIPE_INCLUDED
#define ICONTROLLERPIPE_INCLUDED

#include "embedded_typedefs.h"


class IControllerPipe
{
public:
        virtual ~IControllerPipe() {}
        virtual void    _delay(unsigned long ms)=0;
        virtual  void   _pinMode(INT_8 portid,INT_8 mode)=0;
        virtual  int  _digitalRead(INT_8 portid)=0;
        virtual void    _digitalWrite(INT_8 portid,INT_8 value)=0;

        // serial
        virtual void   _serialBegin(int baudrate)=0;
        virtual int   _serialAvailable()=0;
        virtual void   _serialPrintln(char* bytes)=0;
        virtual void   _serialWrite(_BYTE byte)=0;
        virtual void   _serialPrint(int value)=0;
        virtual void   _serialPrint(float value)=0;
        virtual void   _serialPrint(double value)=0;
        virtual int   _serialRead()=0;

//        // bitwiser serial transmission
//        virtual void serialSendBW(int value,_BYTE* checksum=0)=0;
//        virtual void serialSendBW(float value,_BYTE* checksum=0)=0;
//        virtual void serialSendBW(double value,_BYTE* checksum=0)=0;
//        virtual int serialReadBW_int(_BYTE* checksum=0)=0;
//        virtual float serialReadBW_float(_BYTE* checksum=0)=0;
//        virtual double serialReadBW_double(_BYTE* checksum=0)=0;

        //timer1
        virtual void _timer1_initialize(long microseconds)=0;
        virtual void _timer1_attachInterrupt(void (*isr)(), long microseconds=-1)=0;
        virtual void _timer1_detachInterrupt()=0;
};



#endif // ICONTROLLERPIPE_INCLUDED
