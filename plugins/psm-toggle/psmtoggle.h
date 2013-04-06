#ifndef PSMTOGGLE_H
#define PSMTOGGLE_H

#include "../../system-ui-mt-toggles/mtabstracttoggle.h"
#include <QtPlugin>
#include <QDebug>
#include <QDBusMessage>
#include <QDBusConnection>
#include <MBanner>
#include <MApplication>
#include "qmsystem2/qmdevicemode.h"
#include "qmsystem2/qmbattery.h"

#define ICON_DIR "/usr/share/mt-toggles/psm-toggle/"
#define ACTIVE_ICON ICON_DIR "icon-m-psm-on.png"
#define INACTIVE_ICON ICON_DIR "icon-m-psm-off.png"

class PSMToggle : public QObject, public MTAbstractToggle
{
    Q_OBJECT
    Q_INTERFACES(MTAbstractToggle)
public:
    PSMToggle(QObject *parent = NULL);
    bool isToggle() { return false; }
    bool isWorking() { return m_isWorking; }

    QString toggleName() { return "Power Saving Mode Toggle"; }
    QString toggleDeveloper() { return "Mohammad Abu-Garbeyyeh"; }
    QUrl toggleSupportUrl() { return QUrl("mailto:mohammad7410@gmail.com"); }
    QImage toggleIcon();
    QString toggleIconId() { return QString(); }

    bool isActive();

private:
    MeeGo::QmDeviceMode *m_deviceMode;
    MeeGo::QmBattery *m_deviceBattery;

    bool m_isActive;
    bool m_isWorking;

    bool getIsPSMModeFromPSMState(MeeGo::QmDeviceMode::PSMState state);

public slots:
    void onToggleClicked();
    void onToggleLongPressed();

signals:
    void stateChanged(bool state);
    void iconChanged(QImage icon);
    void iconChanged(QString iconId);
    void isWorkingStateChanged(bool working);

private slots:
    void onPSMStateChanged(MeeGo::QmDeviceMode::PSMState state);
};

#endif // PSMTOGGLE_H
