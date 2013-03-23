#ifndef NFCTOGGLE_H
#define NFCTOGGLE_H

#include "../../system-ui-mt-toggles/mtabstracttoggle.h"
#include <QtPlugin>

#define ACTIVE_ICON "icon-m-service-nfc"
#define INACTIVE_ICON "icon-m-content-nfc-inverse"

class NFCToggle : public QObject, public MTAbstractToggle
{
    Q_OBJECT
    Q_INTERFACES(MTAbstractToggle)

public:
    NFCToggle(QObject *parent = NULL);
    virtual ~NFCToggle();

    QString toggleName() { return "NFC Toggle"; }
    QString toggleDeveloper() { return "Alexander S. Salieff"; }
    QUrl toggleSupportUrl() { return QUrl("mailto:salieff@mail.ru"); }
    QImage toggleIcon() { return QImage(); }
    QString toggleIconId() { return (m_isActive ? ACTIVE_ICON : INACTIVE_ICON); }
    bool isActive() { return m_isActive; }
    bool isToggle() { return true; }

public slots:
    void onToggleClicked();

signals:
    void stateChanged(bool state);
    void iconChanged(QImage icon);
    void iconChanged(QString iconId);
    void isWorkingStateChanged(bool working);

private slots:
    void onRadioStatesChanged(uint st);

private:
    bool requestNFCActivity();
    void setNFCActive(bool a);

    bool m_isActive;
};

#endif // NFCTOGGLE_H
