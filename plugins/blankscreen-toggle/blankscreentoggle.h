#ifndef BLANKSCREEN_H
#define BLANKSCREEN_H

#include "../../system-ui-mt-toggles/mtabstracttoggle.h"
#include <QSystemScreenSaver>
#include <QtPlugin>

#define ACTIVE_ICON "icon-m-telephony-phone-button"
#define INACTIVE_ICON "icon-m-telephony-phone-button-dimmed"

using namespace QtMobility;

class BlankScreenToggle : public QObject, public MTAbstractToggle
{
    Q_OBJECT
    Q_INTERFACES(MTAbstractToggle)

public:
    BlankScreenToggle(QObject *parent = NULL);

    QString toggleName() { return "BlankScreen Toggle"; }
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

private:
    QSystemScreenSaver *m_ssaverControl;
    bool m_isActive;
};

#endif // BLANKSCREEN_H
