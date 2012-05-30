#include "flashlighttoggle.h"

FlashlightToggle::FlashlightToggle(QObject *parent) :
    QObject(parent),
    m_src(0),
    m_isActive(false)
{
    gst_init(NULL, NULL);
    m_src = gst_element_factory_make("subdevsrc", "src");

    if (!m_src)
        return;

    g_object_set(G_OBJECT(m_src), "video-torch", 1, NULL);
    g_object_set(G_OBJECT(m_src), "viewfinder-mode", 1, NULL);
    gst_element_set_state(m_src, GST_STATE_NULL);
}

void FlashlightToggle::onToggleClicked()
{
    setFlashActive(!m_isActive);
}

void FlashlightToggle::setFlashActive(bool active)
{
    if (!m_src)
        return;

    if (active && !m_isActive) {
        gst_element_set_state(m_src, GST_STATE_PLAYING);
        m_isActive = true;
    } else if (!active && m_isActive) {
        gst_element_set_state(m_src, GST_STATE_NULL);
        m_isActive = false;
    }

    emit stateChanged(m_isActive);

    if (m_isActive)
        emit iconChanged(ACTIVE_ICON);
    else
        emit iconChanged(INACTIVE_ICON);
}

Q_EXPORT_PLUGIN2(flashlighttoggle, FlashlightToggle)
