#include <syslog.h>

#include <mce/dbus-names.h>
#include <mce/mode-names.h>

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>

#include "nfctoggle.h"

NFCToggle::NFCToggle(QObject *parent) :
    QObject(parent),
    m_isActive(false)
{
    openlog("NFCToggle", 0, LOG_USER);

    if (QDBusConnection::systemBus().isConnected())
    {
        m_isActive = requestNFCActivity();
        if (!QDBusConnection::systemBus().connect(MCE_SERVICE, MCE_SIGNAL_PATH, MCE_SIGNAL_IF, MCE_RADIO_STATES_SIG, this, SLOT(onRadioStatesChanged(uint))))
            syslog(LOG_ERR, "Constructor: Can't connect onRadioStatesChanged");
    }
    else
    {
        syslog(LOG_ERR, "Constructor: System bus isn't connected");
    }
}

NFCToggle::~NFCToggle()
{
    closelog();
}

void NFCToggle::onToggleClicked()
{
    setNFCActive(!m_isActive);
}

void NFCToggle::onRadioStatesChanged(uint st)
{
    syslog(LOG_DEBUG, "onRadioStatesChanged: %u", st);

    m_isActive = ((st & MCE_RADIO_STATE_NFC) != 0);
    emit stateChanged(m_isActive);
    emit iconChanged(m_isActive ? ACTIVE_ICON : INACTIVE_ICON);
}

bool NFCToggle::requestNFCActivity()
{
    QDBusInterface iface(MCE_SERVICE, MCE_REQUEST_PATH, MCE_REQUEST_IF, QDBusConnection::systemBus());
    if (!iface.isValid())
    {
        syslog(LOG_ERR, "requestNFCActivity: interface isn't valid");
        return false;
    }

    QDBusReply<uint> st = iface.call(MCE_RADIO_STATES_GET);
    if (!st.isValid())
    {
        syslog(LOG_ERR, "requestNFCActivity: reply isn't valid");
        return false;
    }

    syslog(LOG_DEBUG, "requestNFCActivity: %u", st.value());
    return ((st.value() & MCE_RADIO_STATE_NFC) != 0);
}

void NFCToggle::setNFCActive(bool a)
{
    if (!QDBusConnection::systemBus().isConnected())
    {
        syslog(LOG_ERR, "setNFCActive: System bus isn't connected");
        return;
    }

    uint mask = MCE_RADIO_STATE_NFC;
    uint st = a ? MCE_RADIO_STATE_NFC : 0;

    QDBusInterface iface(MCE_SERVICE, MCE_REQUEST_PATH, MCE_REQUEST_IF, QDBusConnection::systemBus());
    if (!iface.isValid())
    {
        syslog(LOG_ERR, "setNFCActive: interface isn't valid");
        return;
    }

    QDBusMessage ret = iface.call(MCE_RADIO_STATES_CHANGE_REQ, st, mask);
    if (ret.type() == QDBusMessage::ErrorMessage)
        syslog(LOG_ERR, "setNFCActive: Can't call MCE_RADIO_STATES_CHANGE_REQ [%s:%s]", ret.errorName().toLocal8Bit().constData(), ret.errorMessage().toLocal8Bit().constData());
}

Q_EXPORT_PLUGIN2(nfctoggle, NFCToggle)
