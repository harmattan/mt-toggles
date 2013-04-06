#include "wifitoggle.h"

WifiToggle::WifiToggle(QObject *parent) :
    QObject(parent),
    m_isWorking(false),
    m_isWifiOn(false)
{
    getWifiState();

    QDBusConnection connection = QDBusConnection::connectToBus(QDBusConnection::SystemBus, "wifi-toggle");

    connection.connect("", "", "com.nokia.mce.signal", "radio_states_ind", this,
                       SLOT(getWifiState()));
}

void WifiToggle::onToggleClicked()
{
    setWifiEnabled(!m_isWifiOn);
}

void WifiToggle::onToggleLongPressed()
{
    QDBusMessage message = QDBusMessage::createMethodCall("com.nokia.DuiControlPanel", "/",
                                                          "com.nokia.DuiControlPanelIf", "appletPage");
    QList<QVariant> args;
    args.append(QVariant("Internet"));
    message.setArguments(args);

    QDBusConnection bus = QDBusConnection::sessionBus();

    if (bus.isConnected())
        bus.send(message);
}

void WifiToggle::setWifiEnabled(bool enableWifi)
{
    quint32 state, mask;
    state = mask = 0;

    if (enableWifi) {
        state |= MCE_RADIO_STATE_WLAN;
        mask |= MCE_RADIO_STATE_WLAN;
    } else {
        state &= ~MCE_RADIO_STATE_WLAN;
        mask |= MCE_RADIO_STATE_WLAN;
    }

    QDBusInterface interface(MCE_SERVICE, MCE_REQUEST_PATH,
                             MCE_REQUEST_IF, QDBusConnection::systemBus(), this);
    interface.call(QDBus::NoBlock, MCE_RADIO_STATES_CHANGE_REQ, state, mask);
}

bool WifiToggle::wifiStateFromRadioStates(qint32 states)
{
    if (states & MCE_RADIO_STATE_WLAN) {
        return true;
    } else {
        return false;
    }
}

void WifiToggle::getWifiState()
{
    QDBusReply<quint32> radioStatesReply =
            QDBusConnection::systemBus().call(QDBusMessage::createMethodCall(MCE_SERVICE, MCE_REQUEST_PATH,
                                                                             MCE_REQUEST_IF, MCE_RADIO_STATES_GET));

    if (radioStatesReply.isValid()) {
        m_isWifiOn = wifiStateFromRadioStates(radioStatesReply.value());
    } else {
        qDebug() << "Invalid DBus reply";
    }

    emit stateChanged(m_isWifiOn);
    emit iconChanged(toggleIcon());
}

void WifiToggle::onRadioStateChanged(const qint32 state)
{
    m_isWifiOn = wifiStateFromRadioStates(state);
    emit stateChanged(isActive());
}

bool WifiToggle::isActive()
{
    return m_isWifiOn;
}

QImage WifiToggle::toggleIcon()
{
    if (isActive())
        return QImage(ACTIVE_ICON);
    else
        return QImage(INACTIVE_ICON);
}

Q_EXPORT_PLUGIN2(wifitoggle, WifiToggle)
