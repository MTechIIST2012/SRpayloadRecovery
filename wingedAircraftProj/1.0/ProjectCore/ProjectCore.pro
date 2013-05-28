#-------------------------------------------------
#
# Project created by QtCreator 2013-02-19T23:26:44
#
#-------------------------------------------------

QT       -= gui
QT       += network


CONFIG += qt3d
CONFIG(debug, debug|release) {
     BUILDTYPE = 'debug'
 } else {
     BUILDTYPE = 'release'
 }
DESTDIR = $${PWD}/../bin/$${BUILDTYPE}/

INCLUDEPATH += $${PWD}/../interfaces\
                $${PWD}/../common\
                $${PWD}/../Utilities\
                $${PWD}/../../../communication/interfaces\
                $${PWD}/../../../thirdparty/qserialport/include

DEPENDPATH += $${PWD}/../interfaces\
                $${PWD}/../common\
                $${PWD}/../Utilities\
                $${PWD}/../../../communication/interfaces\
                $${PWD}/../../../thirdparty/qserialport/include

LIBS += -L$${PWD}/../bin/$${BUILDTYPE} -lUtilities\
        -L$${PWD}/../../../thirdparty/qserialport/bin -lSerialPort\


TARGET = ProjectCore
TEMPLATE = lib

DEFINES += PROJECTCORE_LIBRARY

SOURCES += \
    command.cpp \
    commanddata.cpp \
    communication/tcpsocketpipe.cpp \
    communication/serialpipe.cpp \
    communication/databasepipe.cpp \
    communication/gscontrollerpipe.cpp \
    communication/timerclient.cpp

HEADERS +=\
        ProjectCore_global.h \
    command.h \
    commanddata.h \
    communication/tcpsocketpipe.h \
    communication/serialpipe.h \
    communication/databasepipe.h \
    communication/gscontrollerpipe.h \
    communication/timerclient.h
