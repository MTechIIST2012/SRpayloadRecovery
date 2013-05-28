#-------------------------------------------------
#
# Project created by QtCreator 2013-02-24T17:42:56
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = TestManagerArchitechture
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    testmanager.cpp


CONFIG(debug, debug|release) {
     BUILDTYPE = 'debug'
 } else {
     BUILDTYPE = 'release'
 }

DESTDIR = $${PWD}/../../bin/$${BUILDTYPE}

INCLUDEPATH += $${PWD}/../../ProjectCore\
                $${PWD}/../../interfaces\
                $${PWD}/../../common\
                $${PWD}/../../Utilities

DEPENDPATH +=   $${PWD}/../../ProjectCore\
                $${PWD}/../../interfaces\
                $${PWD}/../../common\
                $${PWD}/../../Utilities

LIBS += -L$${DESTDIR} -lProjectCore\
        -L$${DESTDIR} -lUtilities\
        -L$${PWD}/../../../../thirdparty/qserialport/bin -lSerialPort\

HEADERS += \
    testmanager.h
