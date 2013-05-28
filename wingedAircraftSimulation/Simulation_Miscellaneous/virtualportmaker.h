#ifndef VIRTUALPORTMAKER_H
#define VIRTUALPORTMAKER_H

#include <QObject>
#include <QList>
#include <QPair>

class QProcess;
class PortConnectInfo;

class VirtualPortMaker : public QObject
{
    Q_OBJECT
public:
    explicit VirtualPortMaker(QObject *parent = 0);
    ~VirtualPortMaker();
    QPair<QString,QString> createPortPair();
    QString findPair(QString port);
    const QList<PortConnectInfo*>& getPortConnInfoList();
    void removePair(QString port1,QString port2);
    void clearAll();
private:
    QList<PortConnectInfo*> mPortConnInfoList;
};

class PortConnectInfo
{
public:
    PortConnectInfo(QString port1,
                    QString port2,
                    QProcess* process);
    QString getPort1();
    QString getPort2();
    QProcess* getProcess();
private:
    QString mPort1;
    QString mPort2;
    QProcess* mProcess;
};

#endif // VIRTUALPORTMAKER_H
