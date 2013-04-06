QT -= gui
QT += dbus

TARGET = cellnetworkmode-toggle
TEMPLATE = lib
CONFIG += plugin

SOURCES += networkmodetoggle.cpp

HEADERS += networkmodetoggle.h

target.path = /usr/lib/mt-toggles
