#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("MissionSimulator");
    a.setApplicationVersion("1.0a");

    MainWindow w;
    w.show();

    return a.exec();
}
