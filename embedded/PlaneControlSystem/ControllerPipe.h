#ifndef CONTROLLERPIPE_H
#define CONTROLLERPIPE_H

#include "IControllerPipe.h"

class ControllerPipe   :   public  IControllerPipe
{
    public:
        ControllerPipe();
        virtual ~ControllerPipe();

        virtual void    _delay(unsigned long ms);
        virtual  void   _pinMode(INT_8 portid,INT_8 mode);
        virtual  int  _digitalRead(INT_8 portid);
        virtual void    _digitalWrite(INT_8 portid,INT_8 value);

        // serial
        virtual void   _serialBegin(int baudrate);
        virtual int   _serialAvailable();
        virtual void   _serialPrintln(char* bytes);
        virtual void   _serialWrite(_BYTE byte);
        virtual void   _serialPrint(int value);
        virtual void   _serialPrint(float value);
        virtual void   _serialPrint(double value);
        virtual int   _serialRead();

        //timer1
        virtual void _timer1_initialize(long microseconds);
        virtual void _timer1_attachInterrupt(void (*isr)(), long microseconds=-1);
        virtual void _timer1_detachInterrupt();
};

#endif // CONTROLLERPIPE_H
