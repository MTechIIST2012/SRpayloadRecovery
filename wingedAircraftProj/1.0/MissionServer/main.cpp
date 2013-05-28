#include <QtCore/QCoreApplication>
#include "missionserver.h"
#include <QDebug>
#include <stdio.h>
#include <iostream>


using namespace std;

void readString(char* str);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setApplicationName("MissionServer");
    a.setApplicationVersion("1.0a");

    char devPort[20];
    char devBaud[10];
    cout << "Enter device port :";
    readString(devPort);
    cout << "Enter baud rate :";
    readString(devBaud);

    QString deviceport(devPort);
    deviceport = deviceport.trimmed();
    int baud = QString(devBaud).trimmed().toInt();

    MissionServer server(deviceport,baud,0);
    server.init();
    server.start();

    return a.exec();
}

void readString(char* str)
{
    int i=0;
    do
    {
        scanf ("%c",&str[i]);
    }while(str[i++] != '\n');
    str[i] = '\0';
}
