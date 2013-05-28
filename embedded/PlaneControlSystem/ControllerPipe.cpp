#include "ControllerPipe.h"
#include "_String.h"
#include <Arduino.h>
#include "TimerOne.h"

ControllerPipe::ControllerPipe()
{
}

ControllerPipe::~ControllerPipe()
{
}

void ControllerPipe::_delay(unsigned long ms)
{
          delay(ms);
}

void  ControllerPipe:: _pinMode(INT_8 portid,INT_8 mode)
{
          pinMode(portid,mode);
}

int ControllerPipe:: _digitalRead(INT_8 portid)
{
          return digitalRead(portid);
}

void    ControllerPipe::_digitalWrite(INT_8 portid,INT_8 value)
{
          digitalWrite(portid,value);
}

void  ControllerPipe:: _serialBegin(int baudrate)
{
          Serial.begin(baudrate);
}

 int  ControllerPipe:: _serialAvailable()
 {
           return Serial.available();
 }

void  ControllerPipe::_serialPrintln(char* bytes)
{
          Serial.println(bytes);
}

void  ControllerPipe:: _serialWrite(_BYTE byte)
{
          Serial.write(byte);
}
void  ControllerPipe:: _serialPrint(int value)
{
          Serial.print(value);
}
void   ControllerPipe::_serialPrint(float value)
{
          Serial.print(value);
}

void  ControllerPipe::_serialPrint(double value)
{
          Serial.print(value);
}

int  ControllerPipe::_serialRead()
{
          return Serial.read();
}

void ControllerPipe::_timer1_initialize(long microseconds)
{
          Timer1.initialize(microseconds);
}

void ControllerPipe::_timer1_attachInterrupt(void (*isr)(), long microseconds)
{
          Timer1.attachInterrupt(isr,microseconds);
}

void ControllerPipe::_timer1_detachInterrupt()
{
          Timer1.detachInterrupt();
}
