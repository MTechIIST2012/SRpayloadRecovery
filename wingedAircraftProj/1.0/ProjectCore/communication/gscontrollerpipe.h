#ifndef GSCONTROLLERPIPE_H
#define GSCONTROLLERPIPE_H

#include "ProjectCore_global.h"
#include "IControllerPipe.h"
#include <QObject>

class TimerClient;

class PROJECTCORESHARED_EXPORT GSControllerPipe : public IControllerPipe
{
public:
    GSControllerPipe();
    virtual ~GSControllerPipe();
    virtual void _delay(unsigned long ms);

    // functions not used
    virtual  void _pinMode(INT_8 portid,INT_8 mode);
    virtual  int _digitalRead(INT_8 portid);
    virtual void _digitalWrite(INT_8 portid,INT_8 value);

    //timer1
    virtual void _timer1_initialize(long microseconds);
    virtual void _timer1_attachInterrupt(void (*isr)(), long microseconds=-1);
    virtual void _timer1_detachInterrupt();
private:
    TimerClient* mTimerClient;
};




#endif // GSCONTROLLERPIPE_H
