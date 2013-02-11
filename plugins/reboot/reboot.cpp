#include "reboot.h"
#include <qmsystemstate.h>
#include <QDebug>

Reboot::Reboot(QObject *parent) :
    QObject(parent),
    m_state(new MeeGo::QmSystemState(this))
{

}

void Reboot::onToggleClicked()
{
  if (!m_state->set(MeeGo::QmSystemState::Reboot)) {
    qWarning() << "Failed to reboot";
  }
}

Q_EXPORT_PLUGIN2(reboot, Reboot)
