#include "rotationmeter.h"
#include <qpainter.h>
#include <qwt_dial_needle.h>
#include <qwt_round_scale_draw.h>

RotationMeter::RotationMeter(QWidget* parent)
    : QwtDial(parent)
{
    initUi();
    setLabel("degree");
}

RotationMeter::~RotationMeter()
{

}

void RotationMeter::setLabel(QString label)
{
    mLabel = label;
    update();
}

QString RotationMeter::getLabel()
{
    return mLabel;
}

double RotationMeter::getRotation()
{
    return value();
}

void RotationMeter::setRotation(double angle)
{
    setValue(angle);
}

void RotationMeter::drawScaleContents( QPainter *painter,const QPointF &center, double radius ) const
{
    QRectF rect( 0.0, 0.0, 2.0 * radius, 2.0 * radius - 10.0 );
    rect.moveCenter( center );

    const QColor color = Qt::black;//palette().color( QPalette::Text );
    painter->setPen( color );

    const int flags = Qt::AlignBottom | Qt::AlignHCenter;
    painter->drawText( rect, flags, mLabel );
}
void RotationMeter::initUi()
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

    setOrigin( 90 );
    setScaleArc( 0, 360 );
    setScale(16,32);
    setRange(-180,180);
    //scaleDraw()->setPenWidth( 10 );
    setFrameShadow(QwtDial::Sunken);
    setLineWidth(4);

    QwtDialSimpleNeedle *needle = new QwtDialSimpleNeedle(
        QwtDialSimpleNeedle::Arrow, true, Qt::red,
        QColor( Qt::gray ).light( 130 ) );
    setNeedle( needle );
}
