#include "mtogglewidget.h"

MToggleWidget::MToggleWidget(QGraphicsItem *parent, QImage icon, QString iconId, bool isToggle) :
    MWidget(parent),
    m_stateImage(NULL)
{
    QGraphicsLinearLayout *layout = new QGraphicsLinearLayout(Qt::Vertical, this);
    MFeedback* feedback = new MFeedback(FEEDBACK_PATTERN, this);
    connect(this, SIGNAL(pressed()), feedback, SLOT(play()));

    m_iconWidget = new MImageWidget(this);
    m_iconWidget->setAspectRatioMode(Qt::KeepAspectRatio);
    m_iconWidget->setMinimumSize(64, 64);
    m_iconWidget->setMaximumSize(64, 64);

    setMinimumSize(80, 80);
    setMaximumSize(80, 80);

    bool weHaveAnImage = false;

    if (!iconId.isEmpty()) {
        weHaveAnImage = true;
        m_iconWidget->setImage(iconId);
    }

    if (!icon.isNull() && !weHaveAnImage) {
        weHaveAnImage = true;
        m_iconWidget->setImage(icon);
    }

    layout->addItem(m_iconWidget);
    layout->setSpacing(0.1);

    if (isToggle) {
        m_stateImage = new MImageWidget(this);
        m_stateImage->setMinimumSize(60, 20);
        m_stateImage->setMaximumSize(60, 20);
        m_stateImage->setAspectRatioMode(Qt::KeepAspectRatio);
        m_stateImage->setImage(QImage(OFF_SWITCH));
        layout->addItem(m_stateImage);
        layout->setAlignment(m_stateImage, Qt::AlignHCenter);
    } else {
        layout->addStretch();
    }
}

void MToggleWidget::onStateChanged(bool state)
{
    if (m_stateImage == NULL)
        return;

    if (state)
        m_stateImage->setImage(QImage(ON_SWITCH));
    else
        m_stateImage->setImage(QImage(OFF_SWITCH));
}

void MToggleWidget::onIconChanged(QImage icon)
{
    m_iconWidget->setImage(icon);
}

void MToggleWidget::mousePressEvent(QGraphicsSceneMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) {
        m_pressed = true;
        emit pressed();
    }
}

void MToggleWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) {
        m_pressed = false;
        emit released();
        if (rect().contains(ev->pos())) {
            emit clicked();
        }
    }
}

void MToggleWidget::setIcon(QString iconId)
{
    m_iconWidget->setImage(iconId);
}
