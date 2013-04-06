#ifndef MTTOGGLESCONTROLLER_H
#define MTTOGGLESCONTROLLER_H

#include <MWidget>
#include <MPannableViewport>
#include <MPannableWidget>
#include <MPositionIndicator>
#include <QGraphicsItem>
#include <QGraphicsLinearLayout>
#include <QPluginLoader>
#include <QDir>
#include <QDebug>
#include <QTimeLine>
#include <QTimer>
#include <QPointF>
#include <QSettings>

#include <mtabstracttoggle.h>
#include "mtogglewidget.h"

#define TOGGLES_DIR "/usr/lib/mt-toggles"

class MTTogglesPlugin;

class MTTogglesController : public MWidget
{
    Q_OBJECT
public:
    explicit MTTogglesController(MTTogglesPlugin *mttogglesPlugin, QGraphicsItem *parent = NULL);
    ~MTTogglesController();

signals:
    
public slots:

private:
    QGraphicsLinearLayout *m_mainLayout;
    QList<QObject*> m_toggleObjects;

    void loadToggles();
    QMap<QObject*,MToggleWidget*> m_toggleMap;
    MTTogglesPlugin *m_mtTogglesPlugin;
    MPannableViewport *m_viewPort;
    QTimeLine *m_timeline;

    bool event(QEvent *event);
    bool m_shouldResetPosition;

private slots:
    void hideStatusMenu();
    void onTimelineFrameChanged(int frame);
};

#endif // MTTOGGLESCONTROLLER_H
