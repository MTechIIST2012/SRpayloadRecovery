#-------------------------------------------------
#
# Project created by QtCreator 2013-04-30T13:23:43
#
#-------------------------------------------------

QT       += core gui

TARGET = WingedAircraftSimulator
TEMPLATE = app

CONFIG(debug, debug|release) {
     BUILDTYPE = 'debug'
 } else {
     BUILDTYPE = 'release'
 }
DESTDIR = $${PWD}/../bin/$${BUILDTYPE}/


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += $${PWD}/../common\
         $${PWD}/../AvrDeviceSimulator\
         $${PWD}/../Simulation_Miscellaneous

LIBS += -L$${DESTDIR} -lAvrDeviceSimulator\
        -L$${DESTDIR} -lPlaneSimulationCore\
        -L$${DESTDIR} -lSimulation_Miscellaneous\
        -L/usr/local/qwt-6.0.3-svn/lib -lqwt\
        -L$${PWD}/../../thirdparty/qserialport/bin -lSerialPort

INCLUDEPATH += /usr/local/qwt-6.0.3-svn/include\
                $${PWD}/../../embedded/interfaces\
                $${PWD}/../../embedded/interfaces/controlledObj\
                $${PWD}/../../embedded/interfaces/meters\
                $${PWD}/../../communication/interfaces\
                $${PWD}/../../communication/src\
                $${PWD}/../PlaneSimulationCore

DEPENDPATH += /usr/local/qwt-6.0.3-svn/include\
                $${PWD}/../../embedded/interfaces\
                $${PWD}/../../embedded/interfaces/controlledObj\
                $${PWD}/../../embedded/interfaces/meters\
                $${PWD}/../../communication/interfaces\
                $${PWD}/../../communication/src\
                $${PWD}/../PlaneSimulationCore

RESOURCES += \
    resources.qrc
