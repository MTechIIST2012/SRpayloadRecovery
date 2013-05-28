#-------------------------------------------------
#
# Project created by QtCreator 2013-02-21T18:43:56
#
#-------------------------------------------------

QT       += core gui
CONFIG   += qt3d

TARGET = MissionViewer
TEMPLATE = app

CONFIG += qt3d
CONFIG(debug, debug|release) {
     BUILDTYPE = 'debug'
 } else {
     BUILDTYPE = 'release'
 }
DESTDIR = $${PWD}/../bin/$${BUILDTYPE}/

INCLUDEPATH += $${PWD}/../ControlLib\
                $${PWD}/../ControlLib/advacedglview\
                $${PWD}/../ControlLib/viewer\
                $${PWD}/../ControlLib/widgets\
                $${PWD}/../FlightDynamicsCore\
                $${PWD}/../interfaces\
                $${PWD}/../interfaces/plane\
                $${PWD}/../common\
                $${PWD}/../Utilities\
                $${PWD}/../ProjectCore\
                $${PWD}/../ProjectCore/communication\
                $${PWD}/../../../communication/interfaces\
                $${PWD}/../../../communication/src\
                '/usr/local/qwt-6.0.3-svn/include'

DEPENDPATH += $${PWD}/../ControlLib\
                $${PWD}/../ControlLib/advacedglview\
                $${PWD}/../ControlLib/viewer\
                $${PWD}/../ControlLib/widgets\
                $${PWD}/../FlightDynamicsCore\
                $${PWD}/../interfaces\
                $${PWD}/../interfaces/plane\
                $${PWD}/../common\
                $${PWD}/../Utilities\
                $${PWD}/../ProjectCore\
                $${PWD}/../ProjectCore/communication\
                $${PWD}/../../../communication/interfaces\
                $${PWD}/../../../communication/src\
                '/usr/local/qwt-6.0.3-svn/include'

LIBS += -L$${PWD}/../bin/$${BUILDTYPE} -lUtilities\
        -L$${PWD}/../bin/$${BUILDTYPE} -lControlLib\
        -L$${PWD}/../bin/$${BUILDTYPE} -lProjectCore\
        -L$${PWD}/../bin/$${BUILDTYPE} -lFlightDynamicsCore\
        -L'/usr/local/qwt-6.0.3-svn/lib' -lqwt\
        -L$${PWD}/../../../thirdparty/qserialport/bin -lSerialPort\


SOURCES += main.cpp\
        missionviewer.cpp \
    ../../../communication/src/DataPackets_E.cpp \
    ../../../communication/src/Communication_E.cpp \
    ../../../communication/src/_CircularBuffer.cpp \
    ../../../communication/src/_String.cpp \
    ../../../communication/src/_StringList.cpp \
    connectiondialog.cpp \
    googleearthconnection.cpp \
    aboutdialog.cpp

HEADERS  += missionviewer.h \
    ../../../communication/interfaces/IControllerPipe.h \
    ../../../communication/interfaces/ICommunication_E.h \
    ../../../communication/interfaces/IBuffer_E.h \
    ../../../communication/interfaces/embedded_typedefs.h \
    ../../../communication/src/DataPackets_E.h \
    ../../../communication/src/Communication_E.h \
    ../../../communication/src/_CircularBuffer.h \
    ../../../communication/interfaces/_LinkedList.h \
    ../../../communication/src/_String.h \
    ../../../communication/src/_StringList.h \
    connectiondialog.h \
    googleearthconnection.h \
    aboutdialog.h \
    MissionViewerCommon.h

FORMS    += \
    connectiondialog.ui \
    aboutdialog.ui

RESOURCES += \
    resources.qrc
