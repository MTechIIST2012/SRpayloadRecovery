#include "contintoolbutton.h"
#include <QTimer>

ContinToolButton::ContinToolButton(QWidget *parent) :
    QToolButton(parent)
{
    mTimer = new QTimer(this);
    setInterval(50);

    connect(mTimer,
            SIGNAL(timeout()),
            this,
            SIGNAL(clickUpdate()));
}

ContinToolButton::~ContinToolButton()
{

}

void ContinToolButton::setInterval(int msec)
{
    mTimer->setInterval(msec);
}

int ContinToolButton::getInterval()
{
    return mTimer->interval();
}

void ContinToolButton::mousePressEvent(QMouseEvent* e)
{
    mTimer->start();
    QToolButton::mousePressEvent(e);
}

void ContinToolButton::mouseReleaseEvent(QMouseEvent* e)
{
    mTimer->stop();
    QToolButton::mouseReleaseEvent(e);
}
