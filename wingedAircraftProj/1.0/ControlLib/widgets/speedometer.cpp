#include "speedometer.h"
#include <qpainter.h>
#include <qwt_dial_needle.h>
#include <qwt_round_scale_draw.h>

SpeedoMeter::SpeedoMeter(QWidget* parent)
    : QwtDial(parent)
{
    initUi();
    setUnit("km/h");
    setMaxSpeed(1000);
}

SpeedoMeter::~SpeedoMeter()
{

}

double SpeedoMeter::getSpeed()
{
    return value();
}

void SpeedoMeter::setUnit(QString unit)
{
    mUnit = unit;
    update();
}

QString SpeedoMeter::getUnit()
{
    return mUnit;
}

void SpeedoMeter::setMaxSpeed(double speed)
{
    mMaxSpeed = speed;
    setRange(0,mMaxSpeed);
}

double SpeedoMeter::getMaxSpeed()
{
    return mMaxSpeed;
}

void SpeedoMeter::setSpeed(double speed)
{
    setValue(speed);
}

void SpeedoMeter::drawScaleContents( QPainter *painter,
    const QPointF &center, double radius ) const
{
    QRectF rect( 0.0, 0.0, 2.0 * radius, 2.0 * radius - 10.0 );
    rect.moveCenter( center );

    const QColor color = Qt::black;//palette().color( QPalette::Text );
    painter->setPen( color );

    const int flags = Qt::AlignBottom | Qt::AlignHCenter;
    painter->drawText( rect, flags, mUnit );
}

void SpeedoMeter::initUi()
{
    mScaleDraw = new QwtDialScaleDraw(this);
    mScaleDraw->setSpacing( 8 );
    mScaleDraw->enableComponent( QwtAbstractScaleDraw::Backbone, false );
    mScaleDraw->setTickLength( QwtScaleDiv::MinorTick, 0 );
    mScaleDraw->setTickLength( QwtScaleDiv::MediumTick, 4 );
    mScaleDraw->setTickLength( QwtScaleDiv::MajorTick, 8 );
    setScaleDraw( mScaleDraw );

    setWrapping( false );
    setReadOnly( true );

    setOrigin( 135.0 );
    setScaleArc( 0.0, 270.0 );
    setScale(10,20);
    //scaleDraw()->setPenWidth( 10 );
    setFrameShadow(QwtDial::Sunken);
    setLineWidth(4);

    QwtDialSimpleNeedle *needle = new QwtDialSimpleNeedle(
        QwtDialSimpleNeedle::Arrow, true, Qt::red,
        QColor( Qt::gray ).light( 130 ) );
    setNeedle( needle );
}

