#-------------------------------------------------
#
# Project created by QtCreator 2013-05-01T18:33:30
#
#-------------------------------------------------

QT       -= gui

TARGET = Simulation_Miscellaneous
TEMPLATE = lib

CONFIG(debug, debug|release) {
     BUILDTYPE = 'debug'
 } else {
     BUILDTYPE = 'release'
 }
DESTDIR = $${PWD}/../bin/$${BUILDTYPE}/

DEFINES += SIMULATION_MISCELLANEOUS_LIBRARY

SOURCES += \
    linearchara.cpp \
    nonlinearchara.cpp \
    virtualportmaker.cpp

HEADERS +=\
        Simulation_Miscellaneous_global.h \
    ICharacteristics.h \
    linearchara.h \
    nonlinearchara.h \
    virtualportmaker.h

INCLUDEPATH += $${PWD}/../common
