#ifndef PLANECONTROLLERSIMULATOR_H
#define PLANECONTROLLERSIMULATOR_H

#include "PlaneSimulationCore_global.h"
#include <QObject>
#include <QHash>
#include <QThread>
#include <QTimer>
#include "embedded_typedefs.h"

class ControllerThread;
class ControllerSimulationPipe;
class IPlane_E;
class ICommunication_E;

class SimAcceleroMeter;
class SimGPS;
class SimGyroMeter;
class SimMagnetoMeter;
class SimPressureSensor;

class SimAileron;
class SimElevator;
class SimEngine;
class SimRudder;
class SimThrust;

class SerialPort;

class PLANESIMULATIONCORESHARED_EXPORT PlaneControllerSimulator : public QObject
{
    Q_OBJECT
public:
    explicit PlaneControllerSimulator(QString simInputPort,QString simOutputPort,QString serialPort,QObject *parent = 0);
    virtual ~PlaneControllerSimulator();
    void startSimulation();
    void stopSimulation();
    void setSerialPort(QString serialPort);
    QString getSerialPort();
    void setPinMode(INT_8 pinId,INT_8 mode);
    INT_8 getPinMode(INT_8 pinId);
    void setPinValue(INT_8 pinId,INT_8 value);
    INT_8 getPinValue(INT_8 pinId);

    // functions for embedded
    void setPinValue_embedded(INT_8 pinId,INT_8 value);
    void setSimInputPort(QString portName);
    void setSimOutputPort(QString portName);
    QString simInputPort();
    QString simOutputPort();

    void _timer1_initialize(long microseconds);
    void _timer1_attachInterrupt(void (*isr)(), long microseconds=-1);
    void _timer1_detachInterrupt();
signals:
    void pinValueChanged(char pinId);
protected:
    virtual double calcPressure(double altitude_ft);
private slots:
    void onValueUpdateTimeout();
    void onTimer1Timeout();
private:
    typedef void (*TimerFunction)();

    QHash<INT_8,INT_8> mPinModeMap;
    QHash<INT_8,INT_8> mPinValueMap;
    QString mSerialPort;
    QString mSimInPortName;
    QString mSimOutPortName;
    ControllerThread* mControllerThread;
    ControllerSimulationPipe* mControllerSimPipe;
    IPlane_E* mPlane;
    ICommunication_E* mComm;
    QTimer* mTmrValueUpdate;
    SerialPort* mSimInputPort;
    SerialPort* mSimOutputPort;
    QTimer* mTimer1;
    TimerFunction fTimerFn;

    // meters
    SimAcceleroMeter* mAcceleroMeter;
    SimGPS* mGPS;
    SimGyroMeter* mGyroMeter;
    SimMagnetoMeter* mMagnetoMeter;
    SimPressureSensor* mPressureSensor;

    // controlled objects
    SimAileron* mAileron;
    SimElevator* mElevator;
    SimEngine* mEngine;
    SimRudder* mRudder;
    SimThrust* mThrust;
};

//////////////////////////////////////////////////////////////////////
class IPlaneController;

class ControllerThread : public QThread
{
    Q_OBJECT
public:
    ControllerThread(IPlane_E* plane,
                     ControllerSimulationPipe* simulationpipe,
                     ICommunication_E* comm,
                     QObject* parent=0);
    ~ControllerThread();
    void startSimulation();
    void run();
private slots:
    void onCorrTimerTimeout();
private:
    ControllerSimulationPipe* mSimulationPipe;
    IPlaneController*  mPlaneController;
    QTimer* mClockCorrTimer;
    IPlane_E* mPlane;
    ICommunication_E* mComm;
};

#endif // PLANECONTROLLERSIMULATOR_H
