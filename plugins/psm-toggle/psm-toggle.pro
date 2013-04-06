#-------------------------------------------------
#
# Project created by QtCreator 2012-05-30T17:57:41
#
#-------------------------------------------------

QT += dbus

TARGET = psm-toggle
TEMPLATE = lib
CONFIG += plugin link_pkgconfig

SOURCES += psmtoggle.cpp

HEADERS += psmtoggle.h

INCLUDEPATH += /usr/include/meegotouch

target.path = /usr/lib/mt-toggles

PKGCONFIG += meegotouch
