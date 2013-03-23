#include "blankscreentoggle.h"

BlankScreenToggle::BlankScreenToggle(QObject *parent) :
    QObject(parent),
    m_ssaverControl(new QSystemScreenSaver(this)),
    m_isActive(false)
{
    m_isActive = m_ssaverControl->screenSaverInhibited();
}

void BlankScreenToggle::onToggleClicked()
{
    m_isActive = !m_isActive;

    m_ssaverControl->setScreenSaverInhibited(m_isActive);
    emit stateChanged(m_isActive);
    emit iconChanged(toggleIconId());
}

Q_EXPORT_PLUGIN2(blankscreentoggle, BlankScreenToggle)
