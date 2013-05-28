#ifndef TCPSERVERTHREAD_H
#define TCPSERVERTHREAD_H

#include <QThread>
#include <QTcpSocket>

class ICommunication_E;

class TcpServerThread : public QThread
{
    Q_OBJECT
public:
    TcpServerThread(QTcpSocket* socket,ICommunication_E* comm,int ID,QObject *parent=0);
    virtual ~TcpServerThread();
    void run();
    void setCommunication(ICommunication_E* comm);
    ICommunication_E* getCommunication();
signals:
    void error(QTcpSocket::SocketError socketError);
    void commDisconnected(ICommunication_E* comm);
private slots:
    void readyRead();
    void disconnected();
private:
    QTcpSocket* mSocket;
    int mSocketDescriptor;
    ICommunication_E* mComm;
};

#endif // TCPSERVERTHREAD_H
