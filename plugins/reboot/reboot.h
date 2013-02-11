// -*- c++ -*-
#ifndef REBOOT_H
#define REBOOT_H

#include "../../system-ui-mt-toggles/mtabstracttoggle.h"
#include <QImage>
#include <QtPlugin>

namespace MeeGo {
  class QmSystemState;
};

class Reboot : public QObject, public MTAbstractToggle
{
    Q_OBJECT
    Q_INTERFACES(MTAbstractToggle)

public:
    Reboot(QObject *parent = 0);
    bool isToggle() { return false; }
    bool isActive() { return true; }

    QString toggleName() { return "Reboot"; }
    QString toggleDeveloper() { return "Mohammad Sameer"; }
    QUrl toggleSupportUrl() { return QUrl("mailto:msameer@foolab.org"); }
    QImage toggleIcon() { return QImage(); }
    QString toggleIconId() { return "icon-m-common-refresh"; }

signals:
    void stateChanged(bool state);
    void isWorkingStateChanged(bool working);

    void iconChanged(QImage icon);
    void iconChanged(QString iconId);

public slots:
    void onToggleClicked();

private:
    MeeGo::QmSystemState *m_state;
};

#endif /* REBOOT_H */
