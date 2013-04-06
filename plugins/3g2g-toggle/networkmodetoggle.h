#ifndef NETWORKMODETOGGLE_H
#define NETWORKMODETOGGLE_H

#include <QObject>
#include "../../system-ui-mt-toggles/mtabstracttoggle.h"

#define ThreeGIcon "icon-m-bluetooth-active"
#define TwoGIcon "icon-m-bluetooth"
#define DualIcon "icon"

class NetworkModeToggle : public QObject, public MTAbstractToggle
{
    Q_OBJECT
    Q_INTERFACES(MTAbstractToggle)

public:
    BluetoothToggle(QObject *parent = NULL);
    QString toggleName() { return "3G/2G Toggle"; }
    QString toggleDeveloper() { return "Mohammad Abu-Garbeyyeh"; }
    QUrl toggleSupportUrl() { return QUrl("mailto:mohammad7410@gmail.com"); }
    QImage toggleIcon() { return QImage(); }
    QString toggleIconId() { return INACTIVE_ICON; }
    bool isActive() { return m_isActive; }
    bool isToggle() { return false; }

public slots:
    void onToggleClicked();
    void onToggleLongPressed();

signals:
    void stateChanged(bool state);
    void iconChanged(QImage icon);
    void iconChanged(QString iconId);
    void isWorkingStateChanged(bool working);

private:


private slots:

};

#endif // NETWORKMODETOGGLE_H
