#ifndef PSMTOGGLE_H
#define PSMTOGGLE_H

#include "../../system-ui-mt-toggles/mtabstracttoggle.h"
#include <QtPlugin>
#include <QDebug>
#include "qmsystem2/qmdevicemode.h"

class PSMToggle : public QObject, public MTAbstractToggle
{
    Q_OBJECT
    Q_INTERFACES(MTAbstractToggle)
public:
    PSMToggle(QObject *parent = NULL);
    bool isToggle() { return true; }
    bool isWorking() { return m_isWorking; }

    QString toggleName() { return "Power Saving Mode Toggle"; }
    QString toggleDeveloper() { return "Mohammad Abu-Garbeyyeh"; }
    QUrl toggleSupportUrl() { return QUrl("mailto:mohammad7410@gmail.com"); }

    QImage toggleIcon();
    QString toggleIconId();

    bool isActive();

private:
    MeeGo::QmDeviceMode *m_deviceMode;

    bool m_isWorking;
    int m_psmAutoPercent;

    bool getIsPSMModeFromPSMState(MeeGo::QmDeviceMode::PSMState state);
    void setIcon(bool isPSM, bool isAuto);

public slots:
    void onToggleClicked();

signals:
    void stateChanged(bool state);
    void iconChanged(QImage icon);
    void iconChanged(QString iconId);
    void isWorkingStateChanged(bool working);

private slots:
    void onPSMStateChanged(MeeGo::QmDeviceMode::PSMState state);
};

#endif // PSMTOGGLE_H
