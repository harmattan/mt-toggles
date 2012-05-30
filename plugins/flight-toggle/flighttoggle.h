#ifndef FLIGHTTOGGLE_H
#define FLIGHTTOGGLE_H

#include "../../system-ui-mt-toggles/mtabstracttoggle.h"
#include <QIcon>
#include <QImage>
#include <QtPlugin>
#include <QDebug>
#include <qmsystem2/qmdevicemode.h>

class FlightToggle : public QObject, public MTAbstractToggle
{
    Q_OBJECT
    Q_INTERFACES(MTAbstractToggle)

public:
    FlightToggle(QObject *parent = NULL);
    bool isToggle() { return true; }
    bool isWorking() { return m_isWorking; }

    QString toggleName() { return "Flight Toggle"; }
    QString toggleDeveloper() { return "Mohammad Abu-Garbeyyeh"; }
    QUrl toggleSupportUrl() { return QUrl("mailto:mohammad7410@gmail.com"); }
    QImage toggleIcon() { return QImage(); }
    QString toggleIconId() { return "icon-m-status-menu-flight-mode"; }

    bool isActive();

private:
    MeeGo::QmDeviceMode *m_deviceMode;

    bool m_isActive;
    bool m_isWorking;

    bool getIsFlightModeFromDeviceMode(MeeGo::QmDeviceMode::DeviceMode mode);

public slots:
    void onToggleClicked();

signals:
    void stateChanged(bool state);
    void iconChanged(QImage icon);
    void iconChanged(QString iconId);
    void isWorkingStateChanged(bool working);

private slots:
    void onDeviceModeChanged(MeeGo::QmDeviceMode::DeviceMode mode);
};

#endif // FLIGHTTOGGLE_H
