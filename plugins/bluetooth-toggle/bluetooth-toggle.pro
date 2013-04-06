#-------------------------------------------------
#
# Project created by QtCreator 2012-05-29T23:19:39
#
#-------------------------------------------------

QT -= gui
QT += dbus

TARGET = bluetooth-toggle
TEMPLATE = lib
CONFIG += plugin

SOURCES += bluetoothtoggle.cpp

HEADERS += bluetoothtoggle.h

CONFIG += mobility
MOBILITY += connectivity

target.path = /usr/lib/mt-toggles
