QT += dbus

TARGET = wifi-toggle
TEMPLATE = lib
CONFIG += plugin link_pkgconfig

SOURCES += wifitoggle.cpp

HEADERS += wifitoggle.h \
    wifitoggle.h \
    wifitoggle.h

INCLUDEPATH += /usr/include/meegotouch

target.path = /usr/lib/mt-toggles

PKGCONFIG += meegotouch
