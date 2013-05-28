#-------------------------------------------------
#
# Project created by QtCreator 2013-05-23T19:37:22
#
#-------------------------------------------------

QT       += core gui

TARGET = TestCommunication
TEMPLATE = app

CONFIG(debug, debug|release) {
     BUILDTYPE = 'debug'
 } else {
     BUILDTYPE = 'release'
 }
DESTDIR = $${PWD}/../../bin/$${BUILDTYPE}/


SOURCES += main.cpp\
        widget.cpp \
    ../../../../communication/src/DataPackets_E.cpp \
    ../../../../communication/src/Communication_E.cpp \
    ../../../../communication/src/_CircularBuffer.cpp \
    ../../../../communication/src/_String.cpp \
    ../../../../communication/src/_StringList.cpp

HEADERS  += widget.h \
    ../../../../communication/interfaces/IControllerPipe.h \
    ../../../../communication/interfaces/ICommunication_E.h \
    ../../../../communication/interfaces/IBuffer_E.h \
    ../../../../communication/interfaces/embedded_typedefs.h \
    ../../../../communication/src/DataPackets_E.h \
    ../../../../communication/src/Communication_E.h \
    ../../../../communication/src/_CircularBuffer.h \
    ../../../../communication/interfaces/_LinkedList.h \
    ../../../../communication/src/_String.h \
    ../../../../communication/src/_StringList.h


FORMS    += widget.ui

INCLUDEPATH +=  $${PWD}/../../FlightDynamicsCore\
                $${PWD}/../../ProjectCore\
                $${PWD}/../../ProjectCore/communication\
                $${PWD}/../../../../communication/interfaces\
                $${PWD}/../../../../communication/src\
                $${PWD}/../../../../thirdparty/qserialport/include

DEPENDPATH +=   $${PWD}/../../FlightDynamicsCore\
                $${PWD}/../../ProjectCore\
                $${PWD}/../../ProjectCore/communication\
                $${PWD}/../../FlightDynamicsCore/communication\
                $${PWD}/../../../../communication/interfaces\
                $${PWD}/../../../../communication/src\
                $${PWD}/../../../../thirdparty/qserialport/include

LIBS += -L$${PWD}/../../../../thirdparty/qserialport/bin -lSerialPort\
        -L$${DESTDIR} -lProjectCore
