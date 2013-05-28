#include "timerclient.h"
#include <QTimer>

TimerClient::TimerClient(GSControllerPipe* pipe,QObject* parent)
    : QObject(parent)
{
    mTimer1 = 0;
    mTimer1Fn = 0;
}

TimerClient::~TimerClient()
{
    if(mTimer1)
    {
        mTimer1->stop();
    }
}

void TimerClient::_timer1_initialize(long microseconds)
{
    if(!mTimer1)
    {
        mTimer1 = new QTimer(this);
        connect(mTimer1,
                SIGNAL(timeout()),
                this,
                SLOT(onTimer1Timeout()));
    }

    mTimer1->setInterval(microseconds/1000);
    mTimer1->start();
}

void TimerClient::_timer1_attachInterrupt(void (*isr)(), long microseconds)
{
    if(mTimer1)
    {
        mTimer1Fn = isr;
        if(microseconds != -1)
            mTimer1->setInterval(microseconds);
    }
}

void TimerClient::_timer1_detachInterrupt()
{
    mTimer1Fn = 0;
}

void TimerClient::onTimer1Timeout()
{
    if(mTimer1Fn)
        mTimer1Fn();
}
