#ifndef BLUETOOTHTOGGLE_H
#define BLUETOOTHTOGGLE_H

#include "../../system-ui-mt-toggles/mtabstracttoggle.h"
#include <QBluetoothLocalDevice>
#include <QtPlugin>

#define ACTIVE_ICON "icon-m-bluetooth-active"
#define INACTIVE_ICON "icon-m-bluetooth"

using namespace QtMobility;

class BluetoothToggle : public QObject, public MTAbstractToggle
{
    Q_OBJECT
    Q_INTERFACES(MTAbstractToggle)

public:
    BluetoothToggle(QObject *parent = NULL);
    QString toggleName() { return "Bluetooth Toggle"; }
    QString toggleDeveloper() { return "Mohammad Abu-Garbeyyeh"; }
    QUrl toggleSupportUrl() { return QUrl("mailto:mohammad7410@gmail.com"); }
    QImage toggleIcon() { return QImage(); }
    QString toggleIconId() { return INACTIVE_ICON; }
    bool isActive() { return m_isActive; }
    bool isToggle() { return true; }

public slots:
    void onToggleClicked();

signals:
    void stateChanged(bool state);
    void iconChanged(QImage icon);
    void iconChanged(QString iconId);
    void isWorkingStateChanged(bool working);

private:
    QBluetoothLocalDevice *m_btLocalDevice;
    bool isBluetoothOnFromMode(QBluetoothLocalDevice::HostMode mode);
    bool m_isActive;

private slots:
    void onBluetoothStateChanged(QBluetoothLocalDevice::HostMode);
};

#endif // BLUETOOTHTOGGLE_H
