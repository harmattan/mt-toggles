#include "psmtoggle.h"

PSMToggle::PSMToggle(QObject *parent) :
    QObject(parent),
    m_deviceMode(new MeeGo::QmDeviceMode(this)),
    m_deviceBattery(new MeeGo::QmBattery(this)),
    m_isWorking(false)
{
    connect(m_deviceMode, SIGNAL(devicePSMStateChanged(MeeGo::QmDeviceMode::PSMState)),
            this, SLOT(onPSMStateChanged(MeeGo::QmDeviceMode::PSMState)));
}

bool PSMToggle::getIsPSMModeFromPSMState(MeeGo::QmDeviceMode::PSMState mode)
{
    bool isPSMMode = false;
    switch (mode) {
    case MeeGo::QmDeviceMode::PSMStateOff:
        isPSMMode = false;
        break;
    case MeeGo::QmDeviceMode::PSMStateOn:
        isPSMMode = true;
        break;
    case MeeGo::QmDeviceMode::PSMError:
        isPSMMode = false;
        break;
    }

    return isPSMMode;
}

bool PSMToggle::isActive()
{
    MeeGo::QmDeviceMode::PSMState mode = m_deviceMode->getPSMState();
    return getIsPSMModeFromPSMState(mode);
}

void PSMToggle::onToggleClicked()
{
    MeeGo::QmBattery::ChargingState chargingState = m_deviceBattery->getChargingState();

    if (chargingState == MeeGo::QmBattery::StateCharging) {
        MBanner *banner = new MBanner();
        banner->setStyleName(MBannerType::InformationBanner);
        banner->setTitle(tr("Power saving mode is disabled while charging"));
        banner->appear(MSceneWindow::DestroyWhenDone);

        return;
    }

    m_isWorking = true;
    emit isWorkingStateChanged(m_isWorking);

    if (isActive())
        m_deviceMode->setPSMState(MeeGo::QmDeviceMode::PSMStateOff);
    else
        m_deviceMode->setPSMState(MeeGo::QmDeviceMode::PSMStateOn);

    m_isWorking = false;
    emit isWorkingStateChanged(m_isWorking);
}

QImage PSMToggle::toggleIcon()
{
    if (isActive())
        return QImage(ACTIVE_ICON);
    else
        return QImage(INACTIVE_ICON);
}

void PSMToggle::onPSMStateChanged(MeeGo::QmDeviceMode::PSMState state)
{
    bool isPSMMode = getIsPSMModeFromPSMState(state);
    m_isActive = isPSMMode;
    emit stateChanged(m_isActive);
    emit iconChanged(toggleIcon());
}

void PSMToggle::onToggleLongPressed()
{
    QDBusMessage message = QDBusMessage::createMethodCall("com.nokia.DuiControlPanel", "/",
                                                          "com.nokia.DuiControlPanelIf", "appletPage");
    QList<QVariant> args;
    args.append(QVariant("Battery"));
    message.setArguments(args);

    QDBusConnection bus = QDBusConnection::sessionBus();

    if (bus.isConnected())
        bus.send(message);
}

Q_EXPORT_PLUGIN2(psmtoggle, PSMToggle)
