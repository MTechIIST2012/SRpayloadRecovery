#-------------------------------------------------
#
# Project created by QtCreator 2013-02-15T23:47:42
#
#-------------------------------------------------

QT       += core gui
CONFIG += qt3d

TARGET = TestControlLib
TEMPLATE = app

CONFIG(debug, debug|release) {
     BUILDTYPE = 'debug'
 } else {
     BUILDTYPE = 'release'
 }

DESTDIR = $${PWD}/../../bin/$${BUILDTYPE}/


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

INCLUDEPATH += $${PWD}/../../ControlLib\
                $${PWD}/../../ControlLib/advacedglview\
                $${PWD}/../../ProjectCore\
                $${PWD}/../../interfaces\
                $${PWD}/../../common\
                $${PWD}/../../Utilities

DEPENDPATH += $${PWD}/../../ControlLib\
                $${PWD}/../../ControlLib/advacedglview\
                $${PWD}/../../ProjectCore\
                $${PWD}/../../interfaces\
                $${PWD}/../../common\
                $${PWD}/../../Utilities

LIBS += -L$${DESTDIR} -lControlLib\
        -L$${DESTDIR} -lProjectCore\
        -L$${DESTDIR} -lUtilities\
        -L$${PWD}/../../../../thirdparty/qserialport/bin -lSerialPort\
        -L'/usr/local/qwt-6.0.3-svn/lib' -lqwt
