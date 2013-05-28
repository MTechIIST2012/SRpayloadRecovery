#include "virtualportmaker.h"
#include <QProcess>
#include <QDebug>
#include <QStringList>

VirtualPortMaker::VirtualPortMaker(QObject *parent) :
    QObject(parent)
{
}

VirtualPortMaker::~VirtualPortMaker()
{
    clearAll();
}

QPair<QString,QString> VirtualPortMaker::createPortPair()
{
    QPair<QString,QString> portpair;
    QProcess* process = new QProcess(this);
    QStringList argu;
    argu << "-d" << "-d" << "PTY:" << "PTY:";
    process->setProcessChannelMode(QProcess::MergedChannels);
    process->start("socat",argu);
    if(process->waitForStarted())
    {
        process->waitForReadyRead();
        QString line1 = process->readLine();
        process->waitForReadyRead();
        QString line2 = process->readLine();

        QStringList line1Parts = line1.split(" ");
        QStringList line2Parts = line2.split(" ");
        if(line1Parts.count() >0 && line2Parts.count()>0)
        {
            portpair.first = line1Parts.last().trimmed();
            portpair.second = line2Parts.last().trimmed();

            qDebug() << "port pair produced :" << portpair;
        }
    }
    else
    {
        qDebug() << "socat did not get started";
        qDebug() << process->errorString();
    }
    return portpair;
}

QString VirtualPortMaker::findPair(QString port)
{
    QString pairport;
    PortConnectInfo* conn = 0;
    foreach(PortConnectInfo* connInfo,mPortConnInfoList)
    {
        if(connInfo->getPort1()==port)
        {
            conn = connInfo;
            break;
        }
    }

    if(conn)
    {
        if(conn->getPort1()==port)
            pairport = conn->getPort2();
        else if(conn->getPort2()==port)
            pairport = conn->getPort1();
    }
    return pairport;
}

const QList<PortConnectInfo*>& VirtualPortMaker::getPortConnInfoList()
{
    return mPortConnInfoList;
}

void VirtualPortMaker::removePair(QString port1,QString port2)
{
    PortConnectInfo* conn = 0;
    foreach(PortConnectInfo* connInfo,mPortConnInfoList)
    {
        if(connInfo->getPort1()==port1 && connInfo->getPort2()==port2)
        {
            conn = connInfo;
            break;
        }
    }

    if(conn)
    {
        QProcess* process = conn->getProcess();
        if(process)
        {
            process->kill();
            delete process;
        }
        mPortConnInfoList.removeAll(conn);
    }
}

void VirtualPortMaker::clearAll()
{
    foreach(PortConnectInfo* connInfo,mPortConnInfoList)
    {
        QProcess* process = connInfo->getProcess();
        if(process)
        {
            process->kill();
            delete process;
        }
    }
    mPortConnInfoList.clear();
}

////////////////////////////////////////////////////////////////////////

PortConnectInfo::PortConnectInfo(QString port1,
                QString port2,
                QProcess* process)
{
    mPort1 = port1;
    mPort2 = port2;
    mProcess = process;
}

QString PortConnectInfo::getPort1()
{
    return mPort1;
}

QString PortConnectInfo::getPort2()
{
    return mPort2;
}

QProcess* PortConnectInfo::getProcess()
{
    return mProcess;
}
