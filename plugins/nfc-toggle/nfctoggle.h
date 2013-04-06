#ifndef NFCTOGGLE_H
#define NFCTOGGLE_H

#include "../../system-ui-mt-toggles/mtabstracttoggle.h"
#include <QIcon>
#include <QImage>
#include <QtPlugin>
#include <QDebug>
#include <QTimer>
#include <QDBusConnection>
#include <QDBusMessage>
#include <QDBusReply>
#include <QDBusInterface>
#include <qmsystem2/qmdevicemode.h>
#include <mce/dbus-names.h>
#include <mce/mode-names.h>

#define ICON_DIR "/usr/share/mt-toggles/nfc-toggle/"
#define ACTIVE_ICON ICON_DIR "icon-m-nfc-on.png"
#define INACTIVE_ICON ICON_DIR "icon-m-nfc-off.png"

class NfcToggle : public QObject, public MTAbstractToggle
{
    Q_OBJECT
    Q_INTERFACES(MTAbstractToggle)

public:
    NfcToggle(QObject *parent = NULL);
    bool isToggle() { return false; }
    bool isWorking() { return m_isWorking; }

    QString toggleName() { return "NFC Toggle"; }
    QString toggleDeveloper() { return "Mohammad Abu-Garbeyyeh"; }
    QUrl toggleSupportUrl() { return QUrl("mailto:mohammad7410@gmail.com"); }
    QImage toggleIcon();
    QString toggleIconId() { return QString(); }

    bool isActive();
    
public slots:
    void onToggleClicked();
    void onToggleLongPressed();

signals:
    void stateChanged(bool state);
    void iconChanged(QImage icon);
    void iconChanged(QString iconId);
    void isWorkingStateChanged(bool working);
    void hideStatusMenu();

private:
    bool m_isWorking;
    bool m_isNfcOn;

private:
    void setNfcEnabled(bool enableNfc);
    bool nfcStateFromRadioStates(qint32 states);

private slots:
    void getNfcState();
    void onRadioStateChanged(const qint32 state);
    void nfcPropertyChanged(QString arg0, QVariant state);
};

#endif // NFCTOGGLE_H
