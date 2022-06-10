#include "XWindow.h"
#include "ObjectManager.h"
#include "Drawing.h"
#include "Event.h"

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
}
}

XWindow::XWindow(XLib::Display* display, RefPtr<GUI::Window> host_window, Gfx::IntRect frame) :
    m_id(ObjectManager::the().add_window(this)),
    m_display(display),
    m_bitmap(Gfx::Bitmap::try_create(Gfx::BitmapFormat::BGRA8888, frame.size()).release_value_but_fixme_should_propagate_errors()),
    m_painter(*m_bitmap)
{
    m_window = host_window;
    set_window(host_window);
    set_relative_rect(frame);
}

void XWindow::event_mask(long mask)
{
    m_event_mask = mask;
}

XWindow* XWindow::parent_window()
{
    return dynamic_cast<XWindow*>(this->parent());
}

void XWindow::paint_event(GUI::PaintEvent& ev)
{
    dbgln("Paint event");

    XLib::XEvent event;
    XLib::XRectangle exposed = xrect_from_intrect(ev.rect());
    event.type = Expose;
    event.xany.window = id();
    event.xexpose.x = exposed.x;
    event.xexpose.y = exposed.y;
    event.xexpose.width = exposed.width;
    event.xexpose.height = exposed.height;
    event.xexpose.count = 0;
    _x_put_event(m_display, event);

    GUI::Painter p(*this);
    p.draw_tiled_bitmap(rect(), m_bitmap);
}