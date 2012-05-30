#ifndef MTTOGGLESPLUGIN_H
#define MTTOGGLESPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <MLibrary>
#include <MStatusIndicatorMenuExtensionInterface>
#include <MApplicationExtensionInterface>
#include <QGraphicsWidget>

class MTTogglesController;

class MTTogglesPlugin : public QObject, public MStatusIndicatorMenuExtensionInterface
{
    Q_OBJECT
    Q_INTERFACES(MStatusIndicatorMenuExtensionInterface MApplicationExtensionInterface)

public:
    explicit MTTogglesPlugin(QObject *parent = 0);

    // Getter for the status indicator menu interface
    MStatusIndicatorMenuInterface *statusIndicatorMenuInterface() const;

    // Methods derived from MStatusIndicatorMenuPlugin
    virtual void setStatusIndicatorMenuInterface(MStatusIndicatorMenuInterface &menuInterface);

    // Methods derived from MApplicationExtensionInterface
    virtual bool initialize(const QString &interface);
    virtual QGraphicsWidget *widget();

signals:

public slots:

private:
    MStatusIndicatorMenuInterface *statusIndicatorMenu;
    MTTogglesController *m_mttogglesController;
};

#endif // MTTOGGLESPLUGIN_H
