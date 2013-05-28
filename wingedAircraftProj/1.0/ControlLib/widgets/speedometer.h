#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <qwt_dial.h>
#include "ControlLib_global.h"

class QwtDialScaleDraw;

class CONTROLLIBSHARED_EXPORT SpeedoMeter : public QwtDial
{
    Q_OBJECT
public:
    SpeedoMeter(QWidget* parent=0);
    virtual ~SpeedoMeter();
    double getSpeed();
    void setUnit(QString unit);
    QString getUnit();
    void setMaxSpeed(double speed);
    double getMaxSpeed();
public slots:
    void setSpeed(double speed);
protected:
    virtual void drawScaleContents( QPainter *painter,const QPointF &center, double radius ) const;
private:
    void initUi();

    QString mUnit;
    double mMaxSpeed;
    QwtDialScaleDraw* mScaleDraw;
};

#endif // SPEEDOMETER_H
