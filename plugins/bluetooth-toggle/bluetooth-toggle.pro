#-------------------------------------------------
#
# Project created by QtCreator 2012-05-29T23:19:39
#
#-------------------------------------------------

QT       -= gui

TARGET = bluetooth-toggle
TEMPLATE = lib
CONFIG += plugin

SOURCES += bluetoothtoggle.cpp

HEADERS += bluetoothtoggle.h

CONFIG += mobility
MOBILITY += connectivity

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
