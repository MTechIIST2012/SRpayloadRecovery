#ifndef MISSIONSERVER_H
#define MISSIONSERVER_H

#include <QObject>

class QTimer;
class ICommunication_E;
class IDataPacket_E;
class TcpServer;

class MissionServer : public QObject
{
    Q_OBJECT
public:
    explicit MissionServer(QString deviceSerialport,
                           int deviceBaudRate,
                           QObject *parent = 0);          // Todo: host port needs to be added
    virtual ~MissionServer();
    void setDeviceSerialPort(QString portname);
    QString getDeviceSerialPort();
    void setDeviceBaud(int baud);
    int getDeviceBaud();
    void init();
    void start();
    void stop();
    bool run();
protected:
    virtual ICommunication_E* createDeviceComm();
    virtual void processPacket(IDataPacket_E* packet);
private slots:
    void onUpdateTimerTimeout();
private:
    void acceptConnection();
    void readPosPacket(IDataPacket_E* packet);

    QTimer* mUpdateTimer;
    ICommunication_E* mDeviceComm;
    QString mDeviceSerialPort;
    int mDeviceSerialBaud;
    TcpServer* mTcpServer;
};

#endif // MISSIONSERVER_H
