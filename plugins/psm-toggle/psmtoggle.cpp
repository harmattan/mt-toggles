#include "psmtoggle.h"

PSMToggle::PSMToggle(QObject *parent) :
    QObject(parent),
    m_deviceMode(new MeeGo::QmDeviceMode(this)),
    m_isWorking(false),
    m_psmAutoPercent(20)
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

void PSMToggle::setIcon(bool isPSM, bool isAuto)
{
    if (isPSM)
    {
        if (isAuto)
            emit iconChanged(QImage(":/psm-auto.png"));
        else
            emit iconChanged("icon-m-energy-management-powersave8");
    }
    else
    {
        if (isAuto)
            emit iconChanged(QImage(":/poweron-auto.png"));
        else
            emit iconChanged("icon-m-energy-management-battery8");
    }
}

QImage PSMToggle::toggleIcon()
{
    bool isAuto = m_deviceMode->getPSMBatteryMode() > 0;
    bool isPSM = isActive();

    if (!isAuto)
        return QImage();

    if (isPSM)
        return QImage(":/psm-auto.png");

    return QImage(":/poweron-auto.png");
}

QString PSMToggle::toggleIconId()
{
    bool isAuto = m_deviceMode->getPSMBatteryMode() > 0;
    bool isPSM = isActive();

    if (isAuto)
        return QString();

    if (isPSM)
        return "icon-m-energy-management-powersave8";

    return "icon-m-energy-management-battery8";
}

bool PSMToggle::isActive()
{
    MeeGo::QmDeviceMode::PSMState mode = m_deviceMode->getPSMState();
    return getIsPSMModeFromPSMState(mode);
}

void PSMToggle::onToggleClicked()
{
    m_isWorking = true;
    emit isWorkingStateChanged(m_isWorking);

    bool isAutoEnabled = m_deviceMode->getPSMBatteryMode() > 0;
    bool isPSMActive = isActive();

    if (isAutoEnabled)
    {
        // Auto -> Save
        m_psmAutoPercent = m_deviceMode->getPSMBatteryMode();
        m_deviceMode->setPSMBatteryMode(0);
        m_deviceMode->setPSMState(MeeGo::QmDeviceMode::PSMStateOn);
    }
    else if (isPSMActive)
    {
        // Save -> PowerOn
        m_deviceMode->setPSMState(MeeGo::QmDeviceMode::PSMStateOff);
    }
    else
    {
        // PowerOn -> Auto
        m_deviceMode->setPSMBatteryMode(m_psmAutoPercent);
        // onPSMStateChanged will not be called, so do it manually
        MeeGo::QmDeviceMode::PSMState state = m_deviceMode->getPSMState();
        onPSMStateChanged(state);
    }

    m_isWorking = false;
    emit isWorkingStateChanged(m_isWorking);
}

void PSMToggle::onPSMStateChanged(MeeGo::QmDeviceMode::PSMState state)
{
    bool isActive = getIsPSMModeFromPSMState(state);
    setIcon(isActive, m_deviceMode->getPSMBatteryMode() > 0);
    emit stateChanged(isActive);
}

Q_EXPORT_PLUGIN2(psmtoggle, PSMToggle)
