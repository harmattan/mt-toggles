#include "dual3g2g.h"

Dual3G2GToggle::Dual3G2GToggle(QObject *parent) :
    QObject(parent),
    m_radioAccess(new Cellular::RadioAccess(this))
{
    connect(m_radioAccess, SIGNAL(modeChanged(int)), this, SLOT(onModeChanged(int)));
}

QImage Dual3G2GToggle::iconForMode(Cellular::RadioAccess::Mode m)
{
    switch (m)
    {
    case Cellular::RadioAccess::OnlyTwoG :
        return QImage(":/2g.png");

    case Cellular::RadioAccess::OnlyThreeG :
        return QImage(":/3g.png");

    default :
        break;
    }

    return QImage(":/dual.png");
}

bool Dual3G2GToggle::activeForMode(Cellular::RadioAccess::Mode m)
{
    if (m == Cellular::RadioAccess::OnlyTwoG)
        return false;

    return true;
}

QImage Dual3G2GToggle::toggleIcon()
{
    Cellular::RadioAccess::Mode m = m_radioAccess->mode();
    return iconForMode(m);
}

bool Dual3G2GToggle::isActive()
{
    Cellular::RadioAccess::Mode m = m_radioAccess->mode();
    return activeForMode(m);
}

void Dual3G2GToggle::onToggleClicked()
{
    Cellular::RadioAccess::Mode m = m_radioAccess->mode();

    switch (m)
    {
    case Cellular::RadioAccess::Unknown :
    case Cellular::RadioAccess::DualMode :
    case Cellular::RadioAccess::ForcedDualMode :
        m = Cellular::RadioAccess::OnlyTwoG;
        break;

    case Cellular::RadioAccess::OnlyTwoG :
        m = Cellular::RadioAccess::OnlyThreeG;
        break;

    case Cellular::RadioAccess::OnlyThreeG :
        m = Cellular::RadioAccess::DualMode;
        break;
    }

    m_radioAccess->setMode(m);

    emit stateChanged(activeForMode(m));
    emit iconChanged(iconForMode(m));
}

void Dual3G2GToggle::onModeChanged(int i)
{
    Cellular::RadioAccess::Mode m = static_cast<Cellular::RadioAccess::Mode>(i);

    emit stateChanged(activeForMode(m));
    emit iconChanged(iconForMode(m));
}

Q_EXPORT_PLUGIN2(dual3g2gtoggle, Dual3G2GToggle)
