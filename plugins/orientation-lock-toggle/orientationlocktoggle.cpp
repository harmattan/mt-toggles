#include "orientationlocktoggle.h"

OrientationLockToggle::OrientationLockToggle(QObject *parent) :
    QObject(parent),
    m_faker(new Faker("left", this))
{

}

void OrientationLockToggle::onToggleClicked()
{
    QString newValue;
    if (m_faker->currentValue() == "left")
        newValue = "top";
    else if (m_faker->currentValue() == "top")
        newValue = "left";

    m_faker->setValue(newValue);

    if (!m_faker->isActive())
        m_faker->start();

    emit iconChanged(toggleIcon());
}

QImage OrientationLockToggle::toggleIcon()
{
    if (!m_faker->isActive()) {
        return iconForState("auto");
    } else {
        return iconForState(m_faker->currentValue());
    }
}

void OrientationLockToggle::onToggleLongPressed()
{
    m_faker->stop();
    emit iconChanged(iconForState(AUTO_ID));
}

QString OrientationLockToggle::getIconPath(QString iconId)
{
    return QString(ICON_INSTALL_PATH) + "/" + iconId + ".png";
}

QImage OrientationLockToggle::iconForState(QString state)
{
    if (state == "left")
        return QImage(getIconPath(PORTRAIT_ID));
    else if (state == "top")
        return QImage(getIconPath(LANDSCAPE_ID));
    else if (state == "auto")
        return QImage(getIconPath(AUTO_ID));
    else
        return QImage(getIconPath(AUTO_ID));
}

Q_EXPORT_PLUGIN2(orientationlocktoggle, OrientationLockToggle)
