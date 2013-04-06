#include "mttogglescontroller.h"
#include "mttogglesplugin.h"

MTTogglesController::MTTogglesController(MTTogglesPlugin *plugin, QGraphicsItem *parent) :
    MWidget(parent),
    m_mtTogglesPlugin(plugin)
{
    MWidget *widget = new MWidget(parent);

    m_mainLayout = new QGraphicsLinearLayout(Qt::Horizontal, widget);
    m_mainLayout->setContentsMargins(7, 0, 0, 14);

    m_viewPort = new MPannableViewport(parent);
    m_viewPort->setWidget(widget);
    m_viewPort->setHorizontalPanningPolicy(MPannableViewport::PanningAlwaysOn);
    m_viewPort->setVerticalPanningPolicy(MPannableViewport::PanningAlwaysOff);
    m_viewPort->positionIndicator()->setEnabled(false);
    m_viewPort->setMinimumHeight(90);

    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Horizontal, this);
    layout->addItem(m_viewPort);

    loadToggles();

    m_timeline = new QTimeLine(700, this);
    m_timeline->setFrameRange(0, 90);
    m_timeline->setDirection(QTimeLine::Backward);
    m_timeline->setCurveShape(QTimeLine::EaseOutCurve);
    connect(m_timeline, SIGNAL(frameChanged(int)), this, SLOT(onTimelineFrameChanged(int)));

    QSettings settings("MohammadAG", "mt-toggles", this);
    m_shouldResetPosition = settings.value("main/reset-position", true).toBool();
}

MTTogglesController::~MTTogglesController()
{

}

void MTTogglesController::onTimelineFrameChanged(int frame)
{
    m_viewPort->setPosition(QPointF(frame, 0));
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
        connect(toggleWidget, SIGNAL(longPressed()), plugin, SLOT(onToggleLongPressed()));
        connect(plugin, SIGNAL(hideStatusMenu()), this, SLOT(hideStatusMenu()));

        m_toggleMap.insert(plugin, toggleWidget);
    }
}

void MTTogglesController::hideStatusMenu()
{
    m_mtTogglesPlugin->statusIndicatorMenuInterface()->hideStatusIndicatorMenu();
}

bool MTTogglesController::event(QEvent *event)
{
    if (m_shouldResetPosition) {
        if (event->type() == QEvent::WindowActivate) {
            m_timeline->start();
        } else if (event->type() == QEvent::Show) {
            m_viewPort->setPosition(QPointF(90, 0));
        }
    }

    return MWidget::event(event);
}
