QT -= gui

TARGET = orientation-lock-toggle
TEMPLATE = lib
CONFIG += plugin

CONFIG += link_pkgconfig
PKGCONFIG += contextprovider-1.0 contextsubscriber-1.0

SOURCES += orientationlocktoggle.cpp \
    fakeproperty.cpp \
    fakepropertyadaptor.cpp \
    faker.cpp

HEADERS += orientationlocktoggle.h \
    fakeproperty.h \
    fakepropertyadaptor.h \
    faker.h \
    orientationlocktoggle.h

target.path = /usr/lib/mt-toggles

contextfiles.path += /usr/share/contextkit/providers
contextfiles.files = com.mohammadag.glol.context
icons += icon-m-orientation-auto.png icon-m-orientation-landscape.png icon-m-orientation-portrait.png
icons.path = /usr/share/orientation-lock-toggle

INSTALLS += contextfiles icons target

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    com.mohammadag.glol.context \
    icons/icon-m-orientation-auto.png \
    icons/icon-m-orientation-landscape.png \
    icons/icon-m-orientation-portrait.png
