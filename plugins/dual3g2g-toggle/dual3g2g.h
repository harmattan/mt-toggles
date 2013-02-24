#ifndef DUAL3G2G_H
#define DUAL3G2G_H_H

#include "../../system-ui-mt-toggles/mtabstracttoggle.h"
#include <RadioAccess>
#include <QtPlugin>

class Dual3G2GToggle : public QObject, public MTAbstractToggle
{
    Q_OBJECT
    Q_INTERFACES(MTAbstractToggle)

public:
    Dual3G2GToggle(QObject *parent = NULL);

    QString toggleName() {
        return "Dual-3G-2G mode toggle";
    }
    QString toggleDeveloper() {
        return "Alexander S. Salieff";
    }
    QUrl toggleSupportUrl() {
        return QUrl("mailto:salieff@mail.ru");
    }
    QString toggleIconId() {
        return "";
    }
    bool isToggle() {
        return true;
    }

    QImage toggleIcon();
    bool isActive();

public slots:
    void onToggleClicked();

signals:
    void stateChanged(bool state);
    void iconChanged(QImage icon);
    void iconChanged(QString iconId);
    void isWorkingStateChanged(bool working);

private slots:
    void onModeChanged(int);

private:
    QImage iconForMode(Cellular::RadioAccess::Mode);
    bool activeForMode(Cellular::RadioAccess::Mode);

    Cellular::RadioAccess *m_radioAccess;
};

#endif // DUAL3G2G_H
