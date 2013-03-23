#include "mttogglescontroller.h"
#include "mttogglesplugin.h"

MTTogglesController::MTTogglesController(MTTogglesPlugin *plugin, QGraphicsItem *parent) :
    MWidget(parent)
{
    Q_UNUSED(plugin)

    QGraphicsWidget *widget = new QGraphicsWidget(this);

    MPannableViewport *viewPort = new MPannableViewport(this);
    viewPort->setHorizontalPanningPolicy(MPannableViewport::PanningAlwaysOn);
    viewPort->setWidget(widget);

    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical, this);
    layout->addItem(widget);

    m_mainLayout = new QGraphicsLinearLayout(Qt::Horizontal, widget);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);

    loadToggles();
}

MTTogglesController::~MTTogglesController()
{

}

void MTTogglesController::loadToggles()
{
    QDir dir(TOGGLES_DIR);
    if (!dir.exists())
        return;

    QStringList toggleList = dir.entryList(QDir::Files);
    if (toggleList.isEmpty())
        return;

    foreach (QString toggleFileName, toggleList) {
        QString absPath = dir.absoluteFilePath(toggleFileName);
        QPluginLoader *loader = new QPluginLoader(absPath, this);
        QObject *plugin = loader->instance();
        if (plugin)
            m_toggleObjects.append(plugin);
    }

    if (m_toggleObjects.isEmpty())
        return;

    foreach (QObject *plugin, m_toggleObjects) {
        MTAbstractToggle *toggle = qobject_cast<MTAbstractToggle*>(plugin);
        MToggleWidget *toggleWidget = new MToggleWidget(this, toggle->toggleIcon(), toggle->toggleIconId(), toggle->isToggle());
        m_mainLayout->addItem(toggleWidget);
        toggleWidget->onStateChanged(toggle->isActive());
        connect(plugin, SIGNAL(stateChanged(bool)), toggleWidget, SLOT(onStateChanged(bool)));
        connect(plugin, SIGNAL(iconChanged(QImage)), toggleWidget, SLOT(onIconChanged(QImage)));
        connect(plugin, SIGNAL(iconChanged(QString)), toggleWidget, SLOT(setIcon(QString)));
        connect(toggleWidget, SIGNAL(clicked()), plugin, SLOT(onToggleClicked()));

        m_toggleMap.insert(plugin, toggleWidget);
    }
}
