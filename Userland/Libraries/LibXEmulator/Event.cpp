#include <AK/Queue.h>
#include <LibThreading/Mutex.h>
#include <LibGUI/Application.h>
#include "ObjectManager.h"
#include "XWindow.h"
#include "Event.h"

#include <sys/ioctl.h>

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
}
}

extern "C" {
#include <unistd.h>
}

static AK::Queue<XLib::XEvent> s_event_queue;

namespace {
class Events {
private:
    XLib::Display* _display;
    Threading::Mutex lock_;
    AK::Vector<XLib::XEvent> list_;

    Events(XLib::Display* display);
    void wait_for_more();

public:
//    static bool is_match(long mask, long event);

    static void init_for(XLib::Display* display);
    static Events& instance_for(XLib::Display* display);

    void add(XLib::XEvent event, bool front = false);
    void wait_for_next(XLib::XEvent* event_return, bool dequeue = true);

//    /* if and only if 'wait' is false can this function return false, i.e. no event found */
//    bool query(AK::Function<bool(XLib::XEvent&)> condition,
//        XLib::XEvent* event_return, bool wait, bool dequeue = true);
};

Events&
Events::instance_for(XLib::Display* display)
{
    return *(Events*)display->trans_conn;
}

void Events::init_for(XLib::Display* display)
{
    if (!display->trans_conn)
        display->trans_conn = (XLib::_XtransConnInfo*)new Events(display);
}

Events::Events(XLib::Display* display)
    : _display(display)
    , lock_()
{
}

//bool Events::is_match(long mask, long event)
//{
//    if (mask == (~NoEventMask))
//        return true;
//
//    switch (event) {
//    case KeyPress:
//        return (mask & KeyPressMask);
//    case KeyRelease:
//        return (mask & KeyReleaseMask);
//    case ButtonPress:
//        return (mask & ButtonPressMask);
//    case ButtonRelease:
//        return (mask & ButtonReleaseMask);
//    case MotionNotify:
//        return (mask & PointerMotionMask);
//    case EnterNotify:
//        return (mask & EnterWindowMask);
//    case LeaveNotify:
//        return (mask & LeaveWindowMask);
//    case FocusIn:
//    case FocusOut:
//        return (mask & FocusChangeMask);
//    case KeymapNotify:
//        return (mask & KeymapStateMask);
//    case Expose:
//    case GraphicsExpose:
//    case NoExpose:
//        return (mask & ExposureMask);
//    case VisibilityNotify:
//        return (mask & VisibilityChangeMask);
//    case ConfigureNotify:
//    case DestroyNotify:
//    case UnmapNotify:
//    case MapNotify:
//    case ReparentNotify:
//    case GravityNotify:
//    case CirculateNotify:
//        return (mask & StructureNotifyMask);
//    case CreateNotify:
//        return (mask & SubstructureNotifyMask);
//    case MapRequest:
//    case ConfigureRequest:
//    case CirculateRequest:
//        return (mask & SubstructureRedirectMask);
//    case ResizeRequest:
//        return (mask & ResizeRedirectMask);
//    case PropertyNotify:
//        return (mask & PropertyChangeMask);
//    case SelectionClear:
//    case SelectionRequest:
//    case SelectionNotify:
//    case ColormapNotify:
//    case ClientMessage:
//    case MappingNotify:
//    default:
//        break;
//    }
//    return false;
//}

void Events::add(XLib::XEvent event, bool front)
{
    event.xany.display = _display;

    Threading::MutexLocker evl(lock_);
    evl.lock();
    _display->last_request_read = _display->request;
    event.xany.serial = _display->request++;
    _display->qlen++;
    if (front)
        list_.prepend(event);
    else
        list_.append(event);
    evl.unlock();

    char dummy[1];
    write(_display->conn_checker, dummy, 1);
}

void Events::wait_for_more()
{
    dbgln("wait_for_more start");
    char dummy[1];
    read(_display->fd, dummy, 1);
    dbgln("wait_for_more end");
}

void Events::wait_for_next(XLib::XEvent* event_return, bool dequeue)
{
    // TODO: avoid spinning;
    while(list_.is_empty()) {
        GUI::Application::the()->event_loop().pump();
    }
//    if (!_display->qlen)
//        wait_for_more();

    Threading::MutexLocker evl(lock_);
    evl.lock();
    *event_return = list_.first();
    if (dequeue) {
        list_.remove(0);
        _display->qlen--;
    }
}

//bool Events::query(AK::Function<bool(XLib::XEvent&)> condition, XLib::XEvent* event,
//    bool wait, bool dequeue)
//{
//    while (true) {
//        Threading::MutexLocker evl(lock_);
//
//        for (auto i = list_.begin(); i != list_.end(); i++) {
//            if (!condition(*i))
//                continue;
//
//            *event = (*i);
//            if (dequeue) {
//                list_.remove(i - list_.begin()); // TODO: this certainly won't work
//                _display->qlen--;
//            }
//            return true;
//        }
//        evl.unlock();
//
//        if (!wait)
//            return false;
//        wait_for_more();
//    }
//    return false;
//}
}

void _x_init_events(XLib::Display* /*dpy*/)
{
//    Events::init_for(dpy);
}

void _x_finalize_events(XLib::Display* dpy)
{
    delete (Events*)dpy->trans_conn;
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