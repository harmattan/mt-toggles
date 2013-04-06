#ifndef FLIGHTTOGGLE_H
#define FLIGHTTOGGLE_H

#include "../../system-ui-mt-toggles/mtabstracttoggle.h"
#include <QIcon>
#include <QImage>
#include <QtPlugin>
#include <QDebug>
#include <QDBusConnection>
#include <QDBusMessage>
#include <qmsystem2/qmdevicemode.h>

#define ICON_DIR "/usr/share/mt-toggles/flight-toggle/"
#define ACTIVE_ICON ICON_DIR "icon-m-flightmode-on.png"
#define INACTIVE_ICON ICON_DIR "icon-m-flightmode-off.png"

class FlightToggle : public QObject, public MTAbstractToggle
{
    Q_OBJECT
    Q_INTERFACES(MTAbstractToggle)

public:
    FlightToggle(QObject *parent = NULL);
    bool isToggle() { return false; }
    bool isWorking() { return m_isWorking; }

    QString toggleName() { return "Flight Toggle"; }
    QString toggleDeveloper() { return "Mohammad Abu-Garbeyyeh"; }
    QUrl toggleSupportUrl() { return QUrl("mailto:mohammad7410@gmail.com"); }
    QImage toggleIcon();
    QString toggleIconId() { return QString(); }

    bool isActive();

private:
    MeeGo::QmDeviceMode *m_deviceMode;

    bool m_isActive;
    bool m_isWorking;

    bool getIsFlightModeFromDeviceMode(MeeGo::QmDeviceMode::DeviceMode mode);

public slots:
    void onToggleClicked();
    void onToggleLongPressed();

signals:
    void stateChanged(bool state);
    void iconChanged(QImage icon);
    void iconChanged(QString iconId);
    void isWorkingStateChanged(bool working);
    void hideStatusMenu();

private slots:
    void onDeviceModeChanged(MeeGo::QmDeviceMode::DeviceMode mode);
};

#endif // FLIGHTTOGGLE_H
