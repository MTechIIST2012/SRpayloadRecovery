#-------------------------------------------------
#
# Project created by QtCreator 2013-04-30T13:29:55
#
#-------------------------------------------------

#QT       += network

TARGET = AvrDeviceSimulator
TEMPLATE = lib

CONFIG(debug, debug|release) {
     BUILDTYPE = 'debug'
 } else {
     BUILDTYPE = 'release'
 }
DESTDIR = $${PWD}/../bin/$${BUILDTYPE}/

INCLUDEPATH += $${PWD}/../common/

DEFINES += AVRDEVICESIMULATOR_LIBRARY

SOURCES += \
    avrdevice.cpp \
    avrdeviceview.cpp

HEADERS +=\
        AvrDeviceSimulator_global.h \
    avrdevice.h \
    avrdeviceview.h

FORMS += \
    avrdeviceview.ui

RESOURCES +=
