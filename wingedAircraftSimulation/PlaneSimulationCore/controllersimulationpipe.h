#ifndef CONTROLLERSIMULATIONPIPE_H
#define CONTROLLERSIMULATIONPIPE_H

#include "IControllerPipe.h"
#include "PlaneSimulationCore_global.h"

class PlaneControllerSimulator;
class SerialPort;

class PLANESIMULATIONCORESHARED_EXPORT ControllerSimulationPipe : public IControllerPipe
{
public:
    ControllerSimulationPipe(PlaneControllerSimulator* planeConSimulator);
    virtual ~ControllerSimulationPipe();

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

    void serialClose();
private:
    PlaneControllerSimulator* mPlaneConSimulator;
    SerialPort* mSerialPort;
};

#endif // CONTROLLERSIMULATIONPIPE_H
