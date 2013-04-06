QT += dbus

TARGET = nfc-toggle
TEMPLATE = lib
CONFIG += plugin link_pkgconfig

SOURCES += nfctoggle.cpp

HEADERS += nfctoggle.h \
    nfctoggle.h

INCLUDEPATH += /usr/include/meegotouch

target.path = /usr/lib/mt-toggles

PKGCONFIG += meegotouch
