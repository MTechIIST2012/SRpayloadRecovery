#ifndef TIMERCLIENT_H
#define TIMERCLIENT_H

#include "ProjectCore_global.h"
#include <QObject>

class QTimer;
class GSControllerPipe;

class PROJECTCORESHARED_EXPORT TimerClient : public QObject
{
    Q_OBJECT
public:
    TimerClient(GSControllerPipe* pipe,QObject* parent=0);
    virtual ~TimerClient();
    virtual void _timer1_initialize(long microseconds);
    virtual void _timer1_attachInterrupt(void (*isr)(), long microseconds=-1);
    virtual void _timer1_detachInterrupt();
private slots:
    void onTimer1Timeout();
private:
    typedef void (*fTimerFn)();

    QTimer* mTimer1;
    fTimerFn mTimer1Fn;
};

#endif // TIMERCLIENT_H
