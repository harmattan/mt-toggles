#ifndef MTTOGGLESCONTROLLER_H
#define MTTOGGLESCONTROLLER_H

#include <MWidget>
#include <MPannableViewport>
#include <QGraphicsItem>
#include <QGraphicsLinearLayout>
#include <QPluginLoader>
#include <QDir>

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
};

#endif // MTTOGGLESCONTROLLER_H
