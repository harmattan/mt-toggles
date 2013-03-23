QT       -= gui

TARGET = blankscreen-toggle
TEMPLATE = lib
CONFIG += plugin

SOURCES += blankscreentoggle.cpp

HEADERS += blankscreentoggle.h

CONFIG += mobility
MOBILITY += systeminfo

target.path = /usr/lib/mt-toggles
