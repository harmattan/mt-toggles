QT += gui
TARGET = reboot
TEMPLATE = lib
CONFIG += plugin link_pkgconfig
PKGCONFIG += qmsystem2

SOURCES += reboot.cpp

HEADERS += reboot.h

target.path = /usr/lib/mt-toggles
