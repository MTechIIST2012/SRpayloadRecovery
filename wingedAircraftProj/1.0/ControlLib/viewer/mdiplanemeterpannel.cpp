#include "mdiplanemeterpannel.h"
#include "ui_mdiplanemeterpannel.h"
#include "IPlane.h"
#include <QTimer>
#include <QCloseEvent>

MdiPlaneMeterPannel::MdiPlaneMeterPannel(IPlane* plane,QWidget *parent) :
    QMdiSubWindow(parent),
    ui(new Ui::MdiPlaneMeterPannel)
{
    ui->setupUi(this);
    setWidget(ui->frameMeterPannel);

    mPlane = plane;
    mRefreshTimer = new QTimer(this);

    connect(mRefreshTimer,
            SIGNAL(timeout()),
            this,
            SLOT(updateUi()));

    setRefreshDelay(50);

    ui->frameMeterPannel->setAutoFillBackground(true);
    ui->frameMeterPannel->setPalette(colorTheme(QColor( Qt::darkGray ).dark( 150 ) ));

    ui->rotMeter_pitch->setLabel("Pitch");
    ui->rotMeter_roll->setLabel("Roll");
    ui->rotMeter_yaw->setLabel("Yaw");
}

MdiPlaneMeterPannel::~MdiPlaneMeterPannel()
{
    delete ui;
}

void MdiPlaneMeterPannel::setRefreshDelay(int ms)
{
    mRefreshTimer->stop();
    mRefreshDelay = ms;
    mRefreshTimer->start();
}

int MdiPlaneMeterPannel::getRefreshDelay()
{
    return mRefreshDelay;
}

void MdiPlaneMeterPannel::updateUi()
{
    if(!mPlane)
        return;

    double velocity = mPlane->getVelocity();
    IPlane::PlaneOrientation orientation = mPlane->getOrientation();
    double altitude = mPlane->getAltitude();
    double latitude = mPlane->getLatitude();
    double longitude = mPlane->getLongitude();

    ui->speedometer->setSpeed(velocity);
    ui->rotMeter_pitch->setRotation(orientation.pitch);
    ui->rotMeter_roll->setRotation(orientation.roll);
    ui->rotMeter_yaw->setRotation(orientation.yaw);

    ui->lblAltitude->setText(QString("%1 m").arg(altitude));
    ui->lblLatitude->setText(QString::number(latitude));
    ui->lblLongitude->setText(QString::number(longitude));
}

void MdiPlaneMeterPannel::closeEvent(QCloseEvent *event)
{
    setVisible(false);
    event->ignore();
}

QPalette MdiPlaneMeterPannel::colorTheme( const QColor &base ) const
{
    QPalette palette;
    palette.setColor( QPalette::Base, base );
    palette.setColor( QPalette::Window, base.dark( 150 ) );
    palette.setColor( QPalette::Mid, base.dark( 110 ) );
    palette.setColor( QPalette::Light, base.light( 170 ) );
    palette.setColor( QPalette::Dark, base.dark( 170 ) );
    palette.setColor( QPalette::Text, base.dark( 200 ).light( 800 ) );
    palette.setColor( QPalette::WindowText, base.dark( 200 ) );

    return palette;
}

