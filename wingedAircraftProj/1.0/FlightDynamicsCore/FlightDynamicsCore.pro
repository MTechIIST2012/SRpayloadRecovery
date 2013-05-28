#-------------------------------------------------
#
# Project created by QtCreator 2013-05-05T17:10:16
#
#-------------------------------------------------

TARGET = FlightDynamicsCore
TEMPLATE = lib

CONFIG(debug, debug|release) {
     BUILDTYPE = 'debug'
 } else {
     BUILDTYPE = 'release'
 }
DESTDIR = $${PWD}/../bin/$${BUILDTYPE}/


DEFINES += FLIGHTDYNAMICSCORE_LIBRARY

SOURCES += \
    plane.cpp \
    controlobject.cpp

HEADERS +=\
        FlightDynamicsCore_global.h \
    plane.h \
    controlobject.h

INCLUDEPATH += $${PWD}/../common\
                $${PWD}/../interfaces\
                $${PWD}/../interfaces/plane\

DEPENDPATH += $${PWD}/../common\
                $${PWD}/../interfaces\
                $${PWD}/../interfaces/plane\
