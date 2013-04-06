#include "nfctoggle.h"

NfcToggle::NfcToggle(QObject *parent) :
    QObject(parent),
    m_isWorking(false),
    m_isNfcOn(false)
{
    getNfcState();

    QDBusConnection connection = QDBusConnection::connectToBus(QDBusConnection::SystemBus, "nfc-toggle");

    connection.connect(MCE_SERVICE, MCE_SIGNAL_PATH, MCE_SIGNAL_IF, MCE_RADIO_STATES_SIG,
                       this, SLOT(onRadioStateChanged(const quint32)));


    connection.connect("", "", "com.nokia.nfc.Adapter", "PropertyChanged", this,
                       SLOT(getNfcState()));

}

QImage NfcToggle::toggleIcon()
{
    if (isActive()) {
        return QImage(ACTIVE_ICON);
    } else {
        return QImage(INACTIVE_ICON);
    }
}

void NfcToggle::onToggleClicked()
{
    setNfcEnabled(!m_isNfcOn);
}

void NfcToggle::onToggleLongPressed()
{
    QDBusMessage message = QDBusMessage::createMethodCall("com.nokia.DuiControlPanel", "/",
                                                          "com.nokia.DuiControlPanelIf", "appletPage");
    QList<QVariant> args;
    args.append(QVariant("Near Field Communication"));
    message.setArguments(args);

    QDBusConnection bus = QDBusConnection::sessionBus();

    if (bus.isConnected())
        bus.send(message);
}

void NfcToggle::setNfcEnabled(bool enableNfc)
{
    quint32 state, mask;
    state = mask = 0;

    if (enableNfc) {
        state |= MCE_RADIO_STATE_NFC;
        mask |= MCE_RADIO_STATE_NFC;
    } else {
        state &= ~MCE_RADIO_STATE_NFC;
        mask |= MCE_RADIO_STATE_NFC;
    }

    QDBusInterface interface(MCE_SERVICE, MCE_REQUEST_PATH,
                             MCE_REQUEST_IF, QDBusConnection::systemBus(), this);
    interface.call(QDBus::NoBlock, MCE_RADIO_STATES_CHANGE_REQ, state, mask);
}

bool NfcToggle::nfcStateFromRadioStates(qint32 states)
{
    if (states & MCE_RADIO_STATE_NFC) {
        return true;
    } else {
        return false;
    }
}

void NfcToggle::getNfcState()
{
    QDBusReply<quint32> radioStatesReply =
            QDBusConnection::systemBus().call(QDBusMessage::createMethodCall(MCE_SERVICE, MCE_REQUEST_PATH,
                                                                             MCE_REQUEST_IF, MCE_RADIO_STATES_GET));

    if (radioStatesReply.isValid()) {
        m_isNfcOn = nfcStateFromRadioStates(radioStatesReply.value());
    } else {
        qDebug() << "Invalid DBus reply";
    }

    emit stateChanged(m_isNfcOn);
    emit iconChanged(toggleIcon());
}

void NfcToggle::onRadioStateChanged(const qint32 state)
{
    m_isNfcOn = nfcStateFromRadioStates(state);
    emit stateChanged(isActive());
}

bool NfcToggle::isActive()
{
    return m_isNfcOn;
}

void NfcToggle::nfcPropertyChanged(QString arg0, QVariant state)
{
    qDebug() << arg0 << state;
    if (arg0 == "State") {
        if (state.toString() == "on")
            m_isNfcOn = true;
        else if (state.toString() == "off")
            m_isNfcOn = false;
    }

    emit stateChanged(m_isNfcOn);
}

Q_EXPORT_PLUGIN2(nfctoggle, NfcToggle)
