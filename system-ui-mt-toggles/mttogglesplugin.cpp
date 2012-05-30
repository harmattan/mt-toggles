#include "mttogglesplugin.h"
#include "mttogglescontroller.h"

Q_EXPORT_PLUGIN2(mttogglesplugin, MTTogglesPlugin)

MTTogglesPlugin::MTTogglesPlugin(QObject *parent) :
    statusIndicatorMenu(0),
    m_mttogglesController(0)
{
    Q_UNUSED(parent)
}

void MTTogglesPlugin::setStatusIndicatorMenuInterface(MStatusIndicatorMenuInterface &menuInterface)
{
    statusIndicatorMenu = &menuInterface;
}

MStatusIndicatorMenuInterface *MTTogglesPlugin::statusIndicatorMenuInterface() const
{
    return statusIndicatorMenu;
}

// Methods derived from MApplicationExtensionInterface
bool MTTogglesPlugin::initialize(const QString &)
{
    m_mttogglesController = new MTTogglesController(this);

    return true;
}

QGraphicsWidget *MTTogglesPlugin::widget()
{
    return m_mttogglesController;
}

M_LIBRARY
