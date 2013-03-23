#ifndef FLASHLIGHTTOGGLE_H
#define FLASHLIGHTTOGGLE_H

#include "../../system-ui-mt-toggles/mtabstracttoggle.h"
#include <QtPlugin>
#include <gst/gst.h>
#include <gst/gstelement.h>

#define INACTIVE_ICON "icon-m-camera-torch-off"
#define ACTIVE_ICON "icon-m-camera-torch-on"

class FlashlightToggle : public QObject, public MTAbstractToggle
{
    Q_OBJECT
    Q_INTERFACES(MTAbstractToggle)

public:
    FlashlightToggle(QObject *parent = NULL);
    QString toggleName() { return "Flashlight Toggle"; }
    QString toggleDeveloper() { return "Mohammad Abu-Garbeyyeh"; }
    QUrl toggleSupportUrl() { return QUrl("mailto:mohammad7410@gmail.com"); }
    QImage toggleIcon() { return QImage(); }
    QString toggleIconId() { return INACTIVE_ICON; }
    bool isActive() { return m_isActive; }
    bool isToggle() { return true; }

private:
    GstElement *m_src;
    bool m_isActive;

    void setFlashActive(bool active);

public slots:
    void onToggleClicked();

signals:
    void stateChanged(bool state);
    void iconChanged(QImage icon);
    void iconChanged(QString iconId);
    void isWorkingStateChanged(bool working);
};

#endif // FLASHLIGHTTOGGLE_H
