#-------------------------------------------------
#
# Project created by QtCreator 2013-05-23T11:34:05
#
#-------------------------------------------------

QT       += core

QT       -= gui

CONFIG += qt3d

CONFIG(debug, debug|release) {
     BUILDTYPE = 'debug'
 } else {
     BUILDTYPE = 'release'
 }
DESTDIR = $${PWD}/../bin/$${BUILDTYPE}/

TARGET = MissionServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../../../communication/src/DataPackets_E.cpp \
    ../../../communication/src/Communication_E.cpp \
    ../../../communication/src/_CircularBuffer.cpp \
    missionserver.cpp \
    ../../../communication/src/_StringList.cpp \
    ../../../communication/src/_String.cpp \
    tcpserverthread.cpp \
    tcpserver.cpp

INCLUDEPATH +=  $${PWD}/../FlightDynamicsCore\
                $${PWD}/../ProjectCore\
                $${PWD}/../ProjectCore/communication\
                $${PWD}/../../../communication/interfaces\
                $${PWD}/../../../communication/src\
                $${PWD}/../../../thirdparty/qserialport/include

DEPENDPATH +=   $${PWD}/../FlightDynamicsCore\
                $${PWD}/../ProjectCore\
                $${PWD}/../ProjectCore/communication\
                $${PWD}/../FlightDynamicsCore/communication\
                $${PWD}/../../../communication/interfaces\
                $${PWD}/../../../communication/src\
                $${PWD}/../../../thirdparty/qserialport/include

HEADERS += \
    ../../../communication/interfaces/IControllerPipe.h \
    ../../../communication/interfaces/ICommunication_E.h \
    ../../../communication/interfaces/IBuffer_E.h \
    ../../../communication/interfaces/embedded_typedefs.h \
    ../../../communication/src/DataPackets_E.h \
    ../../../communication/src/Communication_E.h \
    ../../../communication/src/_CircularBuffer.h \
    missionserver.h \
    ../../../communication/interfaces/_LinkedList.h \
    ../../../communication/src/_StringList.h \
    ../../../communication/src/_String.h \
    tcpserverthread.h \
    tcpserver.h

LIBS += -L$${PWD}/../../../thirdparty/qserialport/bin -lSerialPort\
        -L$${DESTDIR} -lProjectCore
