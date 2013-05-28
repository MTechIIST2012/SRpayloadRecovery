#ifndef ROTATIONMETER_H
#define ROTATIONMETER_H

#include <qwt_dial.h>
#include "ControlLib_global.h"

class QwtDialScaleDraw;

class RotationMeter : public QwtDial
{
    Q_OBJECT
public:
    RotationMeter(QWidget* parent=0);
    virtual ~RotationMeter();
    void setLabel(QString label);
    QString getLabel();
    double getRotation();
public slots:
    void setRotation(double angle);
protected:
    virtual void drawScaleContents( QPainter *painter,const QPointF &center, double radius ) const;
private:
    void initUi();

    QString mLabel;
    double mMaxSpeed;
    QwtDialScaleDraw* mScaleDraw;
};

#endif // ROTATIONMETER_H
