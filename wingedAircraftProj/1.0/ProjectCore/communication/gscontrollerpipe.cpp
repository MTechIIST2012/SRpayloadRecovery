#include "gscontrollerpipe.h"
#include "timerclient.h"
#include <QTime>

GSControllerPipe::GSControllerPipe()
{
    mTimerClient = 0;
}

GSControllerPipe::~GSControllerPipe()
{
    if(mTimerClient)
        delete mTimerClient;
}

void GSControllerPipe::_delay(unsigned long ms)
{
    QTime timeReq = QTime::currentTime().addMSecs(ms);
    while(QTime::currentTime() < timeReq);
}

// functions not used
void GSControllerPipe::_pinMode(INT_8 portid,INT_8 mode)
{

}

int GSControllerPipe::_digitalRead(INT_8 portid)
{
    return -1;
}

void GSControllerPipe::_digitalWrite(INT_8 portid,INT_8 value)
{

}

//timer1
void GSControllerPipe::_timer1_initialize(long microseconds)
{
    if(!mTimerClient)
    {
        mTimerClient = new TimerClient(this);
        mTimerClient->_timer1_initialize(microseconds);
    }
}

void GSControllerPipe::_timer1_attachInterrupt(void (*isr)(), long microseconds)
{
    if(mTimerClient)
    {
        mTimerClient->_timer1_attachInterrupt(isr,microseconds);
    }
}

void GSControllerPipe::_timer1_detachInterrupt()
{
    if(mTimerClient)
    {
        mTimerClient->_timer1_detachInterrupt();
    }
}

