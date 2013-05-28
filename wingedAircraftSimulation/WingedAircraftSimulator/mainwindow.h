#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPair>

#include "embedded_typedefs.h"

namespace Ui {
    class MainWindow;
}

class AvrDevice;
class PlaneControllerSimulator;
class VirtualPortMaker;
class QProcess;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    enum SimStage
    {
        BEFORE_FG_START,
        FG_STARTED,
        SIMULATION_STARTED
    };

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_btnStopSimulation_clicked();
    void on_btnStartSimulation_clicked();
    void on_btnStartFG_clicked();
    void onPinValueChanged(char pinId);
private:
    void refreshUi(SimStage simstage);
    void createVirtualPorts();
    bool startFG();
    void startSimulation();
    void stopSimulation();

    Ui::MainWindow *ui;
    AvrDevice* mAvr;
    PlaneControllerSimulator* mPlaneConSim;
    SimStage mSimStage;
    VirtualPortMaker* virPortMaker;
    QProcess* mFGprocess;
    QPair<QString,QString> mFGserialInPair;
    QPair<QString,QString> mFGserialOutPair;
    QPair<QString,QString> mDeviceSerialInPair;
};

#endif // MAINWINDOW_H
