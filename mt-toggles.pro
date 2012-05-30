TEMPLATE = subdirs

SUBDIRS += \
    system-ui-mt-toggles \
    plugins

OTHER_FILES += \
    debian/changelog \
    debian/README \
    debian/copyright \
    debian/rules \
    debian/control \
    debian/compat \
    debian/*.aegis \
    debian/*.install
