#ifndef CONTINTOOLBUTTON_H
#define CONTINTOOLBUTTON_H

#include <QToolButton>
#include "ControlLib_global.h"

class QTimer;

class CONTROLLIBSHARED_EXPORT ContinToolButton : public QToolButton
{
    Q_OBJECT
public:
    explicit ContinToolButton(QWidget *parent = 0);
    virtual ~ContinToolButton();
    void setInterval(int msec);
    int getInterval();
signals:
    void clickUpdate();
protected:
    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseReleaseEvent(QMouseEvent* e);
private:
    QTimer* mTimer;
};

#endif // CONTINTOOLBUTTON_H
