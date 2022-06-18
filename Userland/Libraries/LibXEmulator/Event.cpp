#include <AK/Queue.h>
#include <LibThreading/Mutex.h>
#include <LibGUI/Application.h>
#include "ObjectManager.h"
#include "XWindow.h"
#include "Event.h"

#include <sys/ioctl.h>

namespace XLib {
extern "C" {
#define register
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#undef register
}
}

extern "C" {
#include <unistd.h>
}

static AK::Queue<XLib::XEvent> s_event_queue;

void _x_init_events(XLib::Display* /*dpy*/)
{
//    Events::init_for(dpy);
}

void _x_finalize_events(XLib::Display* /*dpy*/)
{
//    delete (Events*)dpy->trans_conn;
}

void _x_put_event(XLib::Display* /*display*/, const XLib::XEvent& event)
{
    s_event_queue.enqueue(event);
}

extern "C" int
XLib::XSelectInput(XLib::Display* /*display*/, XLib::Window w, long mask)
{
    auto window = ObjectManager::the().get_window(w);
    if (window.is_null())
        return BadWindow;
    window->event_mask(mask);
    return Success;
}

extern "C" int
XLib::XNextEvent(Display* display, XEvent* event)
{
    dbgln("XNextEvent");
    XFlush(display);
    while(s_event_queue.is_empty()) {
        dbgln("Pump");
        GUI::Application::the()->event_loop().pump(Core::EventLoop::WaitMode::WaitForEvents);
    }
    *event = s_event_queue.dequeue();
    dbgln("Event: {}", event->type);
    return Success;
}

extern "C" int
XLib::XFlush(Display* /*dpy*/)
{
    // We only have the "input buffer" to flush.
//    size_t nbytes;
//    dbgln("XFlush: before ioctl");
//    ioctl(dpy->fd, FIONREAD, &nbytes);
//    dbgln("XFlush: nbytes = {}", nbytes);
//    while (nbytes) {
//        char dummy[16];
//        auto rd = read(dpy->fd, dummy, min(nbytes, sizeof(dummy)));
//        dbgln("XFlush: flushed {} bytes", rd);
//        if (rd > 0)
//            nbytes -= rd;
//    }
//    dbgln("XFlush: Flushed");
    return Success;
}

extern "C" int
XLib::XSync(Display* /*display*/, Bool /*discard*/)
{
    // no-op
    return Success;
}