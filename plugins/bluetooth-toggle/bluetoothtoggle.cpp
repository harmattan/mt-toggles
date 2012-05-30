#include "bluetoothtoggle.h"

BluetoothToggle::BluetoothToggle(QObject *parent) :
    QObject(parent),
    m_btLocalDevice(new QBluetoothLocalDevice(this))
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
        emit iconChanged(ACTIVE_ICON);
    else
        emit iconChanged(INACTIVE_ICON);
}

void BluetoothToggle::onToggleClicked()
{
    if (m_isActive)
        m_btLocalDevice->setHostMode(QBluetoothLocalDevice::HostPoweredOff);
    else
        m_btLocalDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverable);
}

Q_EXPORT_PLUGIN2(bluetoothtoggle, BluetoothToggle)
