#include "XPixmap.h"
#include "ObjectManager.h"

XPixmap::XPixmap(XLib::Display* dpy, Gfx::IntRect frame) :
    m_id(ObjectManager::the().add_pixmap(*this)),
    m_display(dpy),
    m_frame(frame),
    m_bitmap(Gfx::Bitmap::try_create(Gfx::BitmapFormat::RGBA8888, frame.size()).release_value_but_fixme_should_propagate_errors()),
    m_painter(*m_bitmap)
{
}