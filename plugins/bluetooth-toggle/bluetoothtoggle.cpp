#include "bluetoothtoggle.h"

BluetoothToggle::BluetoothToggle(QObject *parent) :
    QObject(parent),
    m_btLocalDevice(new QBluetoothLocalDevice(this)),
    m_isActive(false)
{
    connect(m_btLocalDevice, SIGNAL(hostModeStateChanged(QBluetoothLocalDevice::HostMode)),
            this, SLOT(onBluetoothStateChanged(QBluetoothLocalDevice::HostMode)));

    onBluetoothStateChanged(m_btLocalDevice->hostMode());
}

bool BluetoothToggle::isBluetoothOnFromMode(QBluetoothLocalDevice::HostMode mode)
{
    bool isSwitchedOn = false;
    switch (mode) {
    case QBluetoothLocalDevice::HostPoweredOff:
        isSwitchedOn = false;
        break;
    case QBluetoothLocalDevice::HostDiscoverable:
        isSwitchedOn = true;
        break;
    case QBluetoothLocalDevice::HostDiscoverableLimitedInquiry:
        isSwitchedOn = true;
        break;
    case QBluetoothLocalDevice::HostConnectable:
        isSwitchedOn = true;
        break;
    }

    return isSwitchedOn;
}

void BluetoothToggle::onBluetoothStateChanged(QBluetoothLocalDevice::HostMode mode)
{
    m_isActive = isBluetoothOnFromMode(mode);
    emit stateChanged(m_isActive);

    if (m_isActive)
        emit iconChanged(QImage(ACTIVE_ICON));
    else
        emit iconChanged(QImage(INACTIVE_ICON));
}

void BluetoothToggle::onToggleClicked()
{
    if (m_isActive)
        m_btLocalDevice->setHostMode(QBluetoothLocalDevice::HostPoweredOff);
    else
        m_btLocalDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverable);
}

void BluetoothToggle::onToggleLongPressed()
{
    QDBusMessage message = QDBusMessage::createMethodCall("com.nokia.DuiControlPanel", "/",
                                                          "com.nokia.DuiControlPanelIf", "appletPage");
    QList<QVariant> args;
    args.append(QVariant("Bluetooth"));
    message.setArguments(args);

    QDBusConnection bus = QDBusConnection::sessionBus();

    if (bus.isConnected())
        bus.send(message);
}

QImage BluetoothToggle::toggleIcon()
{
    if (m_isActive)
        return QImage(ACTIVE_ICON);
    else
        return QImage(INACTIVE_ICON);
}

Q_EXPORT_PLUGIN2(bluetoothtoggle, BluetoothToggle)
