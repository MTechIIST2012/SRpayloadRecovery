#-------------------------------------------------
#
# Project created by QtCreator 2013-05-09T22:56:27
#
#-------------------------------------------------

QT       += network

TARGET = PlaneSimulationCore
TEMPLATE = lib

CONFIG(debug, debug|release) {
     BUILDTYPE = 'debug'
 } else {
     BUILDTYPE = 'release'
 }
DESTDIR = $${PWD}/../bin/$${BUILDTYPE}/

DEFINES += PLANESIMULATIONCORE_LIBRARY

SOURCES += \
    ../../embedded/plane_core/PlaneController.cpp \
    planecontrollersimulator.cpp \
    controllersimulationpipe.cpp \
    ../../embedded/plane_core/Plane_E.cpp \
    ../../embedded/plane_core/PathPlanner_E.cpp \
    planemetersimulations.cpp \
    planecontrolledobjsimulations.cpp \
    planesensorsimulations.cpp \
    ../../communication/src/DataPackets_E.cpp \
    ../../communication/src/Communication_E.cpp \
    ../../communication/src/_CircularBuffer.cpp \
    ../../communication/src/_StringList.cpp \
    ../../communication/src/_String.cpp

HEADERS +=\
        PlaneSimulationCore_global.h \
    ../../embedded/interfaces/IPlaneController.h \
    ../../embedded/plane_core/PlaneController.h \
    planecontrollersimulator.h \
    controllersimulationpipe.h \
    ../../embedded/interfaces/controlledObj/IThrust_E.h \
    ../../embedded/interfaces/controlledObj/IRudder_E.h \
    ../../embedded/interfaces/controlledObj/IEngine_E.h \
    ../../embedded/interfaces/controlledObj/IElevator_E.h \
    ../../embedded/interfaces/controlledObj/IAileron_E.h \
    ../../embedded/interfaces/meters/IPressureSensor_E.h \
    ../../embedded/interfaces/meters/IMagnetoMeter_E.h \
    ../../embedded/interfaces/meters/IGyroMeter_E.h \
    ../../embedded/interfaces/meters/IGPS_E.h \
    ../../embedded/interfaces/meters/IAcceleroMeter_E.h \
    ../../embedded/plane_core/Plane_E.h \
    ../../embedded/plane_core/PathPlanner_E.h \
    planemetersimulations.h \
    planecontrolledobjsimulations.h \
    planesensorsimulations.h \
    ../../communication/interfaces/IControllerPipe.h \
    ../../communication/interfaces/ICommunication_E.h \
    ../../communication/interfaces/IBuffer_E.h \
    ../../communication/interfaces/embedded_typedefs.h \
    ../../communication/src/DataPackets_E.h \
    ../../communication/src/Communication_E.h \
    ../../communication/src/_CircularBuffer.h \
    ../../communication/interfaces/_LinkedList.h \
    ../../communication/src/_StringList.h \
    ../../communication/src/_String.h

INCLUDEPATH += $${PWD}/../common\
        $${PWD}/../Simulation_Miscellaneous\
        $${PWD}/../../embedded/common\
        $${PWD}/../../embedded/interfaces\
        $${PWD}/../../embedded/interfaces/controlledObj\
        $${PWD}/../../embedded/interfaces/meters\
        $${PWD}/../../embedded/plane_core\
        $${PWD}/../../communication/interfaces\
        $${PWD}/../../communication/src\
        $${PWD}/../../thirdparty/qserialport/include

DEPENDPATH += $${PWD}/../common\
        $${PWD}/../Simulation_Miscellaneous\
        $${PWD}/../../embedded/common\
        $${PWD}/../../embedded/interfaces\
        $${PWD}/../../embedded/interfaces/controlledObj\
        $${PWD}/../../embedded/interfaces/meters\
        $${PWD}/../../embedded/plane_core\
        $${PWD}/../../communication/interfaces\
        $${PWD}/../../communication/src\
        $${PWD}/../../thirdparty/qserialport/include

LIBS += -L$${DESTDIR} -lSimulation_Miscellaneous\
        -L$${PWD}/../../thirdparty/qserialport/bin -lSerialPort
