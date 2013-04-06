#ifndef ORIENTATIONLOCKTOGGLE_H
#define ORIENTATIONLOCKTOGGLE_H

#include "../../system-ui-mt-toggles/mtabstracttoggle.h"
#include <QtPlugin>

// Thanks to Javispedro for his orientation lock code //
#include "faker.h"
////////////////////////////////////////////////////////

#define ICON_INSTALL_PATH "/usr/share/orientation-lock-toggle"
#define AUTO_ID "icon-m-orientation-auto"
#define LANDSCAPE_ID "icon-m-orientation-landscape"
#define PORTRAIT_ID "icon-m-orientation-portrait"

class OrientationLockToggle : public QObject, public MTAbstractToggle
{
    Q_OBJECT
    Q_INTERFACES(MTAbstractToggle)

public:
    explicit OrientationLockToggle(QObject *parent = 0);
    QString toggleName() { return "Orientation Lock Toggle"; }
    QString toggleDeveloper() { return "Mohammad Abu-Garbeyyeh"; }
    QUrl toggleSupportUrl() { return QUrl("mailto:mohammad7410@gmail.com"); }
    QImage toggleIcon();
    QString toggleIconId() { return QString(); }
    bool isActive() { return false; }
    bool isToggle() { return false; }

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
    Faker *m_faker;
    QString getIconPath(QString iconId);
    QImage iconForState(QString state);
};

#endif // ORIENTATIONLOCKTOGGLE_H
