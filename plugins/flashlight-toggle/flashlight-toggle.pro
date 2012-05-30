#-------------------------------------------------
#
# Project created by QtCreator 2012-05-30T18:29:44
#
#-------------------------------------------------

TARGET = flashlight-toggle
TEMPLATE = lib
CONFIG += plugin

CONFIG += link_pkgconfig
PKGCONFIG += gstreamer-0.10

SOURCES += flashlighttoggle.cpp

HEADERS += flashlighttoggle.h

target.path = /usr/lib/mt-toggles
