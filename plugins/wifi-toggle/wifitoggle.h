#ifndef WIFITOGGLE_H
#define WIFITOGGLE_H

#include "../../system-ui-mt-toggles/mtabstracttoggle.h"
#include <QIcon>
#include <QImage>
#include <QtPlugin>
#include <QDebug>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusReply>
#include <QDBusInterface>
#include <qmsystem2/qmdevicemode.h>
#include <mce/dbus-names.h>
#include <mce/mode-names.h>

#define ICON_DIR "/usr/share/mt-toggles/wifi-toggle/"
#define ACTIVE_ICON ICON_DIR "icon-m-wlan-on.png"
#define INACTIVE_ICON ICON_DIR "icon-m-wlan-off.png"

class WifiToggle : public QObject, public MTAbstractToggle
{
    Q_OBJECT
    Q_INTERFACES(MTAbstractToggle)

public:
    WifiToggle(QObject *parent = NULL);
    bool isToggle() { return false; }
    bool isWorking() { return m_isWorking; }

    QString toggleName() { return "WiFi Toggle"; }
    QString toggleDeveloper() { return "Mohammad Abu-Garbeyyeh"; }
    QUrl toggleSupportUrl() { return QUrl("mailto:mohammad7410@gmail.com"); }
    QImage toggleIcon();
    QString toggleIconId() { return QString(); }

    bool isActive();

public slots:
    void onToggleClicked();
    void onToggleLongPressed();

signals:
    void stateChanged(bool state);
    void iconChanged(QImage icon);
    void iconChanged(QString iconId);
    void isWorkingStateChanged(bool working);
    void hideStatusMenu();

private:
    bool m_isWorking;
    bool m_isWifiOn;

private:
    void setWifiEnabled(bool enableWifi);
    bool wifiStateFromRadioStates(qint32 states);

private slots:
    void getWifiState();
    void onRadioStateChanged(const qint32 state);
};

#endif // WIFITOGGLE_H
