#include "planecontrolswidget.h"
#include "ui_planecontrolswidget.h"
#include "IPlane.h"
#include "PlanePartDefs.h"
#include <QDebug>

PlaneControlsWidget::PlaneControlsWidget(IPlane* plane,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlaneControlsWidget)
{
    ui->setupUi(this);
    mPlane = plane;
    updateUi();
}

PlaneControlsWidget::~PlaneControlsWidget()
{
    delete ui;
}

void PlaneControlsWidget::onValueChange()
{
    updateFlight();
}

void PlaneControlsWidget::updateUi()
{
    if(!mPlane)
        return;
    IControlObject* alerone_l = mPlane->getControlObject(AILERON_LEFT);
    IControlObject* alerone_r = mPlane->getControlObject(AILERON_RIGHT);
    IControlObject* elevator_l = mPlane->getControlObject(ELEVATOR_LEFT);
    IControlObject* elevator_r = mPlane->getControlObject(ELEVATOR_RIGHT);
    IControlObject* rudder = mPlane->getControlObject(RUDDER);
    IControlObject* fan = mPlane->getControlObject(FAN);
    IControlObject* body = mPlane->getControlObject(BODY);

    double alerone_l_angle = 0;
    double alerone_r_angle = 0;
    double elevator_l_angle = 0;
    double elevator_r_angle = 0;
    double rudder_angle = 0;
    double fan_angle = 0;

    double velocity = mPlane->getVelocity();
    IPlane::PlaneOrientation orientation = mPlane->getOrientation();
    double altitude = mPlane->getAltitude();
    double longitude = mPlane->getLongitude();
    double latitude = mPlane->getLatitude();

    if(alerone_l)
        alerone_l_angle = alerone_l->getValue().toDouble();
    if(alerone_r)
        alerone_r_angle = alerone_r->getValue().toDouble();
    if(elevator_l)
        elevator_l_angle = elevator_l->getValue().toDouble();
    if(elevator_r)
        elevator_r_angle = elevator_r->getValue().toDouble();
    if(rudder)
        rudder_angle = rudder->getValue().toDouble();
    if(fan)
        fan_angle = fan->getValue().toDouble();

    ui->spinAleroneL_angle->setValue(alerone_l_angle);
    ui->spinAleroneR_angle->setValue(alerone_r_angle);
    ui->spinElevatorL_angle->setValue(elevator_l_angle);
    ui->spinElevatorR_angle->setValue(elevator_r_angle);
    ui->spinRudder_angle->setValue(rudder_angle);
    ui->spinFanRPM->setValue(fan_angle);

    ui->spinVelocity->setValue(velocity);
    ui->spinPitch->setValue(orientation.pitch);
    ui->spinRoll->setValue(orientation.roll);
    ui->spinYaw->setValue(orientation.yaw);
    ui->spinAltitude->setValue(altitude);
    ui->spinLongitude->setValue(longitude);
    ui->spinLatitude->setValue(latitude);
}

void PlaneControlsWidget::updateFlight()
{
    if(!mPlane)
        return;

    double alerone_l_angle = ui->spinAleroneL_angle->value();
    double alerone_r_angle = ui->spinAleroneR_angle->value();
    double elevator_l_angle = ui->spinElevatorL_angle->value();
    double elevator_r_angle = ui->spinElevatorR_angle->value();
    double rudder_angle = ui->spinRudder_angle->value();
    double fan_angle = ui->spinFanRPM->value();

    double velocity = ui->spinVelocity->value();
    IPlane::PlaneOrientation orientation;
    orientation.pitch = ui->spinPitch->value();
    orientation.roll = ui->spinRoll->value();
    orientation.yaw = ui->spinYaw->value();
    double altitude = ui->spinAltitude->value();
    double longitude = ui->spinLongitude->value();
    double latitude = ui->spinLatitude->value();

    IControlObject* alerone_l = mPlane->getControlObject(AILERON_LEFT);
    IControlObject* alerone_r = mPlane->getControlObject(AILERON_RIGHT);
    IControlObject* elevator_l = mPlane->getControlObject(ELEVATOR_LEFT);
    IControlObject* elevator_r = mPlane->getControlObject(ELEVATOR_RIGHT);
    IControlObject* rudder = mPlane->getControlObject(RUDDER);
    IControlObject* fan = mPlane->getControlObject(FAN);
    IControlObject* body = mPlane->getControlObject(BODY);

    if(alerone_l)
        alerone_l->setValue(alerone_l_angle);
    if(alerone_r)
        alerone_r->setValue(alerone_r_angle);
    if(elevator_l)
        elevator_l->setValue(elevator_l_angle);
    if(elevator_r)
        elevator_r->setValue(elevator_r_angle);
    if(rudder)
        rudder->setValue(rudder_angle);
    if(fan)
        fan->setValue(fan_angle);

    mPlane->setVelocity(velocity);
    mPlane->setOrientation(orientation);
    mPlane->setAltitude(altitude);
    mPlane->setLongitude(longitude);
    mPlane->setLatitude(latitude);
}
