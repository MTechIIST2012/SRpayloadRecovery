#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "virtualportmaker.h"
#include "planecontrollersimulator.h"

#include <QDebug>
#include <QProcess>
#include <QStringList>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("MissionSimulator");
    QIcon icon(":/icons/icons/IIST_Logo.png");
    setWindowIcon(icon);

    virPortMaker = new VirtualPortMaker(this);
    mPlaneConSim = new PlaneControllerSimulator("","","",this);
    mSimStage = BEFORE_FG_START;
    refreshUi(mSimStage);
    mFGprocess = 0;
}

MainWindow::~MainWindow()
{
   // delete mAvr;
    delete ui;

    stopSimulation();
}

void MainWindow::onPinValueChanged(char pinId)
{
    qDebug() << QString("Port %0 value changed to %1").arg((int)pinId).arg((int)mPlaneConSim->getPinValue(pinId));
}

void MainWindow::on_btnStartFG_clicked()
{
    virPortMaker->clearAll();
    createVirtualPorts();
    if(startFG())
    {
        mSimStage = FG_STARTED;

        qDebug() << "Flight gear started";

        // message here.
    }
    refreshUi(mSimStage);
}

void MainWindow::on_btnStartSimulation_clicked()
{
    startSimulation();
    mSimStage = SIMULATION_STARTED;
    refreshUi(mSimStage);
}

void MainWindow::on_btnStopSimulation_clicked()
{
    stopSimulation();
    mSimStage = BEFORE_FG_START;
    refreshUi(mSimStage);
}

void MainWindow::refreshUi(SimStage simstage)
{
    switch(simstage)
    {
    case BEFORE_FG_START:
        ui->btnStartFG->setEnabled(true);
        ui->btnStartSimulation->setEnabled(false);
        ui->btnStopSimulation->setEnabled(false);
        break;
    case FG_STARTED:
        ui->btnStartFG->setEnabled(false);
        ui->btnStartSimulation->setEnabled(true);
        ui->btnStopSimulation->setEnabled(false);
        break;
    case SIMULATION_STARTED:
        ui->btnStartFG->setEnabled(false);
        ui->btnStartSimulation->setEnabled(false);
        ui->btnStopSimulation->setEnabled(true);
        break;
    default:
        ui->btnStartFG->setEnabled(true);
        ui->btnStartSimulation->setEnabled(false);
        ui->btnStopSimulation->setEnabled(false);
    }

    ui->edtFG_inPort->setText(QString("%0 <-> %1").arg(mFGserialInPair.first).arg(mFGserialInPair.second));
    ui->edtFG_outPort->setText(QString("%0 <-> %1").arg(mFGserialOutPair.first).arg(mFGserialOutPair.second));
    ui->edtDeviceSerialInternal->setText(mDeviceSerialInPair.first);
    ui->edtDeviceSerialExt->setText(mDeviceSerialInPair.second);
}

void MainWindow::createVirtualPorts()
{
    mFGserialInPair = virPortMaker->createPortPair();
    mFGserialOutPair = virPortMaker->createPortPair();
    mDeviceSerialInPair = virPortMaker->createPortPair();
}

bool MainWindow::startFG()
{
    mPlaneConSim->setSimInputPort(mFGserialInPair.first);
    mPlaneConSim->setSimOutputPort(mFGserialOutPair.first);
    mPlaneConSim->setSerialPort(mDeviceSerialInPair.first);

    // starting flight gear
    if(!mFGprocess)
        mFGprocess = new QProcess(this);

    mFGprocess->setWorkingDirectory("/usr/games");

    QStringList argu;
    argu << QString("--generic=serial,in,10,%0,1200,MTechProjInputProtocol").arg(mFGserialInPair.second)
            << QString("--generic=serial,out,10,%1,1200,MTechProjOutputProtocol").arg(mFGserialOutPair.second);

    mFGprocess->start("fgfs",argu);
    return mFGprocess->waitForStarted();
}

void MainWindow::startSimulation()
{
    mPlaneConSim->startSimulation();
}

void MainWindow::stopSimulation()
{
    mPlaneConSim->stopSimulation();
    mFGprocess->kill();
    delete mFGprocess;
    virPortMaker->clearAll();
    mFGprocess = 0;
}
