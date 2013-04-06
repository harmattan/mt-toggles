#ifndef FLASHLIGHTTOGGLE_H
#define FLASHLIGHTTOGGLE_H

#include "../../system-ui-mt-toggles/mtabstracttoggle.h"
#include <QtPlugin>
#include <gst/gst.h>
#include <gst/gstelement.h>

#define ICON_DIR "/usr/share/mt-toggles/flashlight-toggle/"
#define ACTIVE_ICON ICON_DIR "icon-m-flashlight-on.png"
#define INACTIVE_ICON ICON_DIR "icon-m-flashlight-off.png"

class FlashlightToggle : public QObject, public MTAbstractToggle
{
    Q_OBJECT
    Q_INTERFACES(MTAbstractToggle)

public:
    FlashlightToggle(QObject *parent = NULL);
    QString toggleName() { return "Flashlight Toggle"; }
    QString toggleDeveloper() { return "Mohammad Abu-Garbeyyeh"; }
    QUrl toggleSupportUrl() { return QUrl("mailto:mohammad7410@gmail.com"); }
    QImage toggleIcon() { return QImage(INACTIVE_ICON); }
    QString toggleIconId() { return QString(); }
    bool isActive() { return m_isActive; }
    bool isToggle() { return false; }

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
