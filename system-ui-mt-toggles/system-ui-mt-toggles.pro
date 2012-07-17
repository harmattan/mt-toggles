QT           += core gui
TEMPLATE      = lib
CONFIG       += plugin gui meegotouch system-ui

TARGET        = statusindicatormenu-mt-toggles

INCLUDEPATH  += /usr/include/meegotouch
INCLUDEPATH  += /usr/include/system-ui

CONFIG += link_pkgconfig
PKGCONFIG += mt-toggles

HEADERS += \
    mttogglesplugin.h \
    mttogglescontroller.h \
    mtabstracttoggle.h \
    mtogglewidget.h

SOURCES += \
    mttogglesplugin.cpp \
    mttogglescontroller.cpp \
    mtogglewidget.cpp

OTHER_FILES += \
    statusindicatormenu-mt-toggles.desktop \
    mt-toggles.pc

target.path = /usr/lib/meegotouch/applicationextensions

desktop.files = statusindicatormenu-mt-toggles.desktop
desktop.path = /usr/share/meegotouch/applicationextensions

switches.files += on_switch.png
switches.files += off_switch.png
switches.path = /usr/share/mt-toggles

INSTALLS += switches target desktop
