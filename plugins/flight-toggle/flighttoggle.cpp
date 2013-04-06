#include "flighttoggle.h"

FlightToggle::FlightToggle(QObject *parent) :
    QObject(parent),
    m_deviceMode(new MeeGo::QmDeviceMode(this)),
    m_isWorking(false)
{
    connect(m_deviceMode, SIGNAL(deviceModeChanged(MeeGo::QmDeviceMode::DeviceMode)),
            this, SLOT(onDeviceModeChanged(MeeGo::QmDeviceMode::DeviceMode)));
}

bool FlightToggle::getIsFlightModeFromDeviceMode(MeeGo::QmDeviceMode::DeviceMode mode)
{
    bool isFlightMode = false;
    switch (mode) {
    case MeeGo::QmDeviceMode::Normal:
        isFlightMode = false;
        break;
    case MeeGo::QmDeviceMode::Flight:
        isFlightMode = true;
        break;
    case MeeGo::QmDeviceMode::Error:
    default:
        isFlightMode = false;
        break;
    }

    return isFlightMode;
}

bool FlightToggle::isActive()
{
    MeeGo::QmDeviceMode::DeviceMode mode = m_deviceMode->getMode();
    return getIsFlightModeFromDeviceMode(mode);
}

void FlightToggle::onToggleClicked()
{
    m_isWorking = true;
    emit isWorkingStateChanged(m_isWorking);

    MeeGo::QmDeviceMode::DeviceMode mode = m_deviceMode->getMode();
    MeeGo::QmDeviceMode::DeviceMode nextMode = MeeGo::QmDeviceMode::Normal;
    switch (mode) {
    case MeeGo::QmDeviceMode::Normal:
        nextMode = MeeGo::QmDeviceMode::Flight;
        break;
    case MeeGo::QmDeviceMode::Flight:
        nextMode = MeeGo::QmDeviceMode::Normal;
        break;
    case MeeGo::QmDeviceMode::Error:
        nextMode = MeeGo::QmDeviceMode::Normal;
        break;
    }

    bool result = m_deviceMode->setMode(nextMode);
    if (!result)
        qDebug() << "Failed to set device mode!";

    m_isWorking = false;
    emit isWorkingStateChanged(m_isWorking);
}

void FlightToggle::onToggleLongPressed()
{
    QDBusMessage message = QDBusMessage::createMethodCall("com.nokia.DuiControlPanel", "/",
                                                          "com.nokia.DuiControlPanelIf", "appletPage");
    QList<QVariant> args;
    args.append(QVariant("Phone network"));
    message.setArguments(args);

    QDBusConnection bus = QDBusConnection::sessionBus();

    if (bus.isConnected())
        bus.send(message);
}

void FlightToggle::onDeviceModeChanged(MeeGo::QmDeviceMode::DeviceMode mode)
{
    bool isFlightMode = getIsFlightModeFromDeviceMode(mode);
    m_isActive = isFlightMode;
    emit stateChanged(m_isActive);
    emit iconChanged(toggleIcon());
}

QImage FlightToggle::toggleIcon()
{
    if (isActive()) {
        return QImage(ACTIVE_ICON);
    } else {
        return QImage(INACTIVE_ICON);
    }
}

Q_EXPORT_PLUGIN2(flighttoggle, FlightToggle)
