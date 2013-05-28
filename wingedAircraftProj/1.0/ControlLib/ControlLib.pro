#-------------------------------------------------
#
# Project created by QtCreator 2013-02-15T23:37:34
#
#-------------------------------------------------



TARGET = ControlLib
TEMPLATE = lib
QT     += gui


CONFIG += qt3d
CONFIG(debug, debug|release) {
     BUILDTYPE = 'debug'
 } else {
     BUILDTYPE = 'release'
 }
DESTDIR = $${PWD}/../bin/$${BUILDTYPE}/

INCLUDEPATH +=  $${PWD}/advacedglview\
                $${PWD}/viewer\
                $${PWD}/widgets\
                $${PWD}/../interfaces\
                $${PWD}/../common\
                $${PWD}/../Utilities\
                $${PWD}/../interfaces/plane\
                '/usr/local/qwt-6.0.3-svn/include'

DEPENDPATH +=   $${PWD}/advacedglview\
                $${PWD}/viewer\
                $${PWD}/../interfaces\
                $${PWD}/../common\
                $${PWD}/../Utilities\
                $${PWD}/../interfaces/plane\
                '/usr/local/qwt-6.0.3-svn/include'

LIBS += -L$${PWD}/../bin/$${BUILDTYPE} -lUtilities\
        -L'/usr/local/qwt-6.0.3-svn/lib' -lqwt


DEFINES += CONTROLLIB_LIBRARY

SOURCES += \
    advacedglview/scenemanager.cpp \
    advacedglview/objectviewinfo.cpp \
    advacedglview/objectinfolistdialog.cpp \
    advacedglview/contintoolbutton.cpp \
    advacedglview/advancedglview.cpp \
    viewer/viewer.cpp \
    viewer/mdi3dview.cpp \
    viewer/mdiplaneview.cpp \
    viewer/planecontrolswidget.cpp \
    widgets/speedometer.cpp \
    viewer/mdiplanemeterpannel.cpp \
    widgets/rotationmeter.cpp \
    viewer/viewselectordialog.cpp

HEADERS +=\
        ControlLib_global.h \
    advacedglview/scenemanager.h \
    advacedglview/objectviewinfo.h \
    advacedglview/objectinfolistdialog.h \
    advacedglview/contintoolbutton.h \
    advacedglview/advancedglview.h \
    viewer/viewer.h \
    viewer/mdi3dview.h \
    viewer/mdiplaneview.h \
    viewer/planecontrolswidget.h \
    widgets/speedometer.h \
    viewer/mdiplanemeterpannel.h \
    widgets/rotationmeter.h \
    viewer/viewselectordialog.h

FORMS += \
    advacedglview/objectinfolistdialog.ui \
    advacedglview/advancedglview.ui \
    viewer/viewer.ui \
    viewer/mdi3dview.ui \
    viewer/planecontrolswidget.ui \
    viewer/mdiplanemeterpannel.ui \
    viewer/viewselectordialog.ui

RESOURCES += \
    advacedglview/advancedglview_icons.qrc

OTHER_FILES += \
    advacedglview/ControlLib.pro.user
