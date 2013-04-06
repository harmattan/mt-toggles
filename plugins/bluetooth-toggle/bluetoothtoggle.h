#ifndef BLUETOOTHTOGGLE_H
#define BLUETOOTHTOGGLE_H

#include "../../system-ui-mt-toggles/mtabstracttoggle.h"
#include <QBluetoothLocalDevice>
#include <QDBusMessage>
#include <QDBusConnection>
#include <QtPlugin>

#define ICON_DIR "/usr/share/mt-toggles/bluetooth-toggle/"
#define ACTIVE_ICON ICON_DIR "icon-m-bluetooth-on.png"
#define INACTIVE_ICON ICON_DIR "icon-m-bluetooth-off.png"

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
    QImage toggleIcon();
    QString toggleIconId() { return QString(); }
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
    QBluetoothLocalDevice *m_btLocalDevice;
    bool isBluetoothOnFromMode(QBluetoothLocalDevice::HostMode mode);
    bool m_isActive;

private slots:
    void onBluetoothStateChanged(QBluetoothLocalDevice::HostMode);
};

#endif // BLUETOOTHTOGGLE_H
