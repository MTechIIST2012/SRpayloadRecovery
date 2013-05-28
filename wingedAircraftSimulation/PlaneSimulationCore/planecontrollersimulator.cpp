#include "planecontrollersimulator.h"
#include "controllersimulationpipe.h"
#include "PlaneController.h"
#include "PathPlanner_E.h"
#include "Plane_E.h"
#include "Communication_E.h"
#include "DataPackets_E.h"
#include "planecontrolledobjsimulations.h"
#include "planemetersimulations.h"
#include "serialport.h"
#include <QDebug>
#include <QStringList>

#define SYSTEM_CLOCK  1e9
#define CONTROLLER_CLOCK 16e6
const unsigned long corrSleep_us = (double)(((1.0/CONTROLLER_CLOCK)-(1.0/SYSTEM_CLOCK))*CONTROLLER_CLOCK)*1e-3*1e6; // us/1 ms


ControllerThread::ControllerThread(IPlane_E* plane,
                                   ControllerSimulationPipe* simulationpipe,
                                   ICommunication_E* comm,
                                   QObject* parent)
    : QThread(parent)
{
    mSimulationPipe = simulationpipe;
    mPlane = plane;
    mComm = comm;

    mClockCorrTimer = new QTimer(this);
    connect(mClockCorrTimer,
            SIGNAL(timeout()),
            this,
            SLOT(onCorrTimerTimeout()));
    mClockCorrTimer->start(1);

    PlaneController::generateInstance(mPlane,mSimulationPipe,mComm);
    mPlaneController =  PlaneController::instance();
}

ControllerThread::~ControllerThread()
{
    mClockCorrTimer->stop();
}

void ControllerThread::onCorrTimerTimeout()
{
    usleep(corrSleep_us);
}

void ControllerThread::startSimulation()
{
    mPlaneController->setup();
}

void ControllerThread::run()
{
    while(1)
    {
        mPlaneController->loop();
    }
    exec();
}

//////////////////////////////////////////////////////////////////////

PlaneControllerSimulator::PlaneControllerSimulator(QString simInputPort,QString simOutputPort,QString serialPort,QObject *parent) :
    QObject(parent)
{
    mSerialPort = serialPort;
    mTimer1 = 0;
    fTimerFn = 0;

    mSimInputPort = new SerialPort(this);
    mSimInputPort->setRate(1200);
    mSimInputPort->setPort(simInputPort);
    mSimOutputPort = new SerialPort(this);
    mSimOutputPort->setRate(1200);
    mSimOutputPort->setPort(simOutputPort);

    mTmrValueUpdate = new QTimer(this);
    connect(mTmrValueUpdate,
            SIGNAL(timeout()),
            this,
            SLOT(onValueUpdateTimeout()));

    mControllerSimPipe = new ControllerSimulationPipe(this);
    PathPlanner_E* pathplanner = new PathPlanner_E();

    IPacketFactory_E* factory = new PacketFactory_E();
    mComm = new Communication_E(factory,mControllerSimPipe,100);
    // meters
    mAcceleroMeter = new SimAcceleroMeter();
    mGPS = new SimGPS();
    mGyroMeter = new SimGyroMeter();
    mMagnetoMeter = new SimMagnetoMeter();
    mPressureSensor = new SimPressureSensor();

    // controlled objects
    mAileron = new SimAileron();
    mElevator = new SimElevator();
    mEngine = new SimEngine();
    mRudder = new SimRudder();
    mThrust = new SimThrust();


    PlaneMeterSet_E meterset;
    meterset.accelerometer = mAcceleroMeter;
    meterset.gps = mGPS;
    meterset.gyrometer = mGyroMeter;
    meterset.magnetometer = mMagnetoMeter;
    meterset.pressuresensor = mPressureSensor;

    PlaneControlledObjSet_E controlledObjSet;
    controlledObjSet.alieron = mAileron;
    controlledObjSet.elevator = mElevator;
    controlledObjSet.engine = mEngine;
    controlledObjSet.rudder = mRudder;
    controlledObjSet.thrust = mThrust;

    PlaneSensorSet_E sensorset;
    // Todo: sensors have to be modeled

    mPlane = new Plane_E(meterset,
                        controlledObjSet,
                        sensorset,
                        pathplanner,
                        mControllerSimPipe);

    mControllerThread = new ControllerThread(mPlane,
                                             mControllerSimPipe,
                                             mComm,
                                             this);
}

PlaneControllerSimulator::~PlaneControllerSimulator()
{
    stopSimulation();
    delete mControllerThread;
    delete mControllerSimPipe;
}

void PlaneControllerSimulator::startSimulation()
{
    // opening ports
    mSimInputPort->setPort(mSimInPortName);
    mSimInputPort->open(QIODevice::ReadWrite);
    mSimOutputPort->setPort(mSimOutPortName);
    mSimOutputPort->open(QIODevice::ReadWrite);

    mControllerThread->start();
    mControllerThread->startSimulation();
    mTmrValueUpdate->start(100);
}

void PlaneControllerSimulator::stopSimulation()
{
    mTmrValueUpdate->stop();

    // closing ports
    // opening ports
    mSimInputPort->close();
    mSimOutputPort->close();
    mControllerSimPipe->serialClose();

    mControllerThread->exit(0);
}

void PlaneControllerSimulator::setSerialPort(QString serialPort)
{
    mSerialPort = serialPort;
}

QString PlaneControllerSimulator::getSerialPort()
{
    return mSerialPort;
}

void PlaneControllerSimulator::setPinMode(INT_8 pinId,INT_8 mode)
{
    mPinModeMap.insert(pinId,mode);
}

INT_8 PlaneControllerSimulator::getPinMode(INT_8 pinId)
{
    return mPinModeMap.value(pinId,_OUTPUT);
}

void PlaneControllerSimulator::setPinValue(INT_8 pinId,INT_8 value)
{
    if(getPinMode(pinId) == _INPUT)
    {
        INT_8 prevValue = getPinValue(pinId);
        mPinValueMap.insert(pinId,value);

        if(prevValue != value)
            emit pinValueChanged(pinId);
    }
}

INT_8 PlaneControllerSimulator::getPinValue(INT_8 pinId)
{
    return mPinValueMap.value(pinId,1);
}

// functions for embedded.
void PlaneControllerSimulator::setPinValue_embedded(INT_8 pinId,INT_8 value)
{
    if(getPinMode(pinId) == _OUTPUT)
    {
        INT_8 prevValue = getPinValue(pinId);
        mPinValueMap.insert(pinId,value);

        if(prevValue != value)
            emit pinValueChanged(pinId);
    }
}

void PlaneControllerSimulator::setSimInputPort(QString portName)
{
    mSimInPortName = portName;
}

void PlaneControllerSimulator::setSimOutputPort(QString portName)
{
    mSimOutPortName = portName;
}

QString PlaneControllerSimulator::simInputPort()
{
    return mSimInputPort->portName();
}

QString PlaneControllerSimulator::simOutputPort()
{
   return mSimOutputPort->portName();
}

void PlaneControllerSimulator::_timer1_initialize(long microseconds)
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

void PlaneControllerSimulator::_timer1_attachInterrupt(void (*isr)(), long microseconds)
{
    if(mTimer1)
    {
        fTimerFn = isr;
        if(microseconds != -1)
        {
            mTimer1->setInterval(microseconds/1000);
        }
    }
}

void PlaneControllerSimulator::_timer1_detachInterrupt()
{
    fTimerFn = 0;
}

double PlaneControllerSimulator::calcPressure(double altitude_ft)    // Todo: needs to be modified.
{
    return altitude_ft;
}

void PlaneControllerSimulator::onValueUpdateTimeout()      // Todo: needs to be modified
{
    // reading meter values
    QString meterReadingStr = mSimOutputPort->readLine();
    mSimOutputPort->flush();
    QStringList ReadingParts = meterReadingStr.split(",");
    if(ReadingParts.count()==9)
    {
        double Accel_x = ReadingParts[0].toDouble();
        double Accel_y = ReadingParts[1].toDouble();
        double Accel_z = ReadingParts[2].toDouble();

        double Latitude = ReadingParts[3].toDouble();
        double Longitude = ReadingParts[4].toDouble();
        double Altitude = ReadingParts[5].toDouble();

        double Pitch = ReadingParts[6].toDouble();
        double Roll = ReadingParts[7].toDouble();
        double Heading = ReadingParts[8].toDouble();

        mAcceleroMeter->setAccel_x(Accel_x);
        mAcceleroMeter->setAccel_y(Accel_y);
        mAcceleroMeter->setAccel_z(Accel_z);

        mGPS->setLatitude(Latitude);
        mGPS->setLongitude(Longitude);
        mGPS->setAltitude(Altitude);

        mGyroMeter->setPitch(Pitch);
        mGyroMeter->setRoll(Roll);
        mGyroMeter->setYaw(Heading);           // Todo: needs to be modified with actual yaw

        mMagnetoMeter->setHeading(Heading);

        mPressureSensor->setPressure(calcPressure(Altitude));

        mAcceleroMeter->setReadState(true);
        mGPS->setReadState(true);
        mGyroMeter->setReadState(true);
        mMagnetoMeter->setReadState(true);
        mPressureSensor->setReadState(true);
    }

    QString simCommand = QString("%0,%1,%2,%3\r").arg(mAileron->getAngle())
                         .arg(mElevator->getAngle())
                         .arg(mRudder->getAngle())
                         .arg(mThrust->getThrust());
    mSimInputPort->write(simCommand.toAscii());

    mAileron->setOperationComplete(true);
    mElevator->setOperationComplete(true);
    mEngine->setOperationComplete(true);
    mRudder->setOperationComplete(true);
    mThrust->setOperationComplete(true);
}

void PlaneControllerSimulator::onTimer1Timeout()
{
    if(fTimerFn)
    {
        fTimerFn();
    }
}
