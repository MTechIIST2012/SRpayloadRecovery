#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>
#include <QSet>

class ICommunication_E;

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    TcpServer(int port,QObject *parent=0);
    virtual ~TcpServer();
    int getPort();
    void startServer();
    QSet<ICommunication_E*> getCommSet();
protected:
    void incomingConnection(int socketDescriptor);
    virtual ICommunication_E* createSocketComm(QTcpSocket* socket);
private slots:
    void onConnDisconnect(ICommunication_E* comm);
private:
    int mPort;
    QSet<ICommunication_E*> mCommList;
};

#endif // TCPSERVER_H
