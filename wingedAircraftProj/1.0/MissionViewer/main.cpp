#include <QtGui/QApplication>
#include "missionviewer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("MissionViewer");
    a.setApplicationVersion("1.0a");

    MissionViewer w;
    w.show();

    return a.exec();
}
