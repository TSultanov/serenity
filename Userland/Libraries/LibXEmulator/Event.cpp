#include <LibThreading/Mutex.h>
#include "ObjectManager.h"
#include "XWindow.h"
#include "Event.h"

#include <sys/ioctl.h>

namespace XLib {

extern "C" {
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#include <unistd.h>
}
}

using namespace XLib;

namespace {
class Events {
private:
    Display* _display;
    Threading::Mutex lock_;
    AK::Vector<XEvent> list_;

    Events(Display* display);
    void wait_for_more();

public:
    static bool is_match(long mask, long event);

    static void init_for(Display* display);
    static Events& instance_for(Display* display);

    void add(XEvent event, bool front = false);
    void wait_for_next(XEvent* event_return, bool dequeue = true);

    /* if and only if 'wait' is false can this function return false, i.e. no event found */
    bool query(AK::Function<bool(const XEvent&)> condition,
        XEvent* event_return, bool wait, bool dequeue = true);
};
}

Events&
Events::instance_for(Display* display)
{
    return *(Events*)display->trans_conn;
}

void
_x_init_events(Display* dpy)
{
    Events::init_for(dpy);
}

void
_x_finalize_events(Display* dpy)
{
    delete (Events*)dpy->trans_conn;
}

void
Events::init_for(Display* display)
{
    if (!display->trans_conn)
        display->trans_conn = (XLib::_XtransConnInfo*)new Events(display);
}

Events::Events(Display* display)
    : _display(display)
    , lock_()
{
}

bool Events::is_match(long mask, long event)
{
    if (mask == (~NoEventMask))
        return true;

    switch(event) {
    case KeyPress:
        return (mask & KeyPressMask);
    case KeyRelease:
        return (mask & KeyReleaseMask);
    case ButtonPress:
        return (mask & ButtonPressMask);
    case ButtonRelease:
        return (mask & ButtonReleaseMask);
    case MotionNotify:
        return (mask & PointerMotionMask);
    case EnterNotify:
        return (mask & EnterWindowMask);
    case LeaveNotify:
        return (mask & LeaveWindowMask);
    case FocusIn:
    case FocusOut:
        return (mask & FocusChangeMask);
    case KeymapNotify:
        return (mask & KeymapStateMask);
    case Expose:
    case GraphicsExpose:
    case NoExpose:
        return (mask & ExposureMask);
    case VisibilityNotify:
        return (mask & VisibilityChangeMask);
    case ConfigureNotify:
    case DestroyNotify:
    case UnmapNotify:
    case MapNotify:
    case ReparentNotify:
    case GravityNotify:
    case CirculateNotify:
        return (mask & StructureNotifyMask);
    case CreateNotify:
        return (mask & SubstructureNotifyMask);
    case MapRequest:
    case ConfigureRequest:
    case CirculateRequest:
        return (mask & SubstructureRedirectMask);
    case ResizeRequest:
        return (mask & ResizeRedirectMask);
    case PropertyNotify:
        return (mask & PropertyChangeMask);
    case SelectionClear:
    case SelectionRequest:
    case SelectionNotify:
    case ColormapNotify:
    case ClientMessage:
    case MappingNotify:
    default:
        break;
    }
    return false;
}

void
Events::add(XEvent event, bool front)
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

void
_x_put_event(Display* display, const XEvent& event)
{
    Events::instance_for(display).add(event);
}

void
Events::wait_for_more()
{
    char dummy[1];
    read(_display->fd, dummy, 1);
}

void
Events::wait_for_next(XEvent* event_return, bool dequeue)
{
    if (!_display->qlen)
        wait_for_more();

    Threading::MutexLocker evl(lock_);
    evl.lock();
    *event_return = list_.first();
    if (dequeue) {
        list_.remove(0);
        _display->qlen--;
    }
}

bool
Events::query(AK::Function<bool(const XEvent&)> condition, XEvent* event,
    bool wait, bool dequeue)
{
    while (true) {
        Threading::MutexLocker evl(lock_);

        for (auto i = list_.begin(); i != list_.end(); i++) {
            if (!condition(*i))
                continue;

            *event = (*i);
            if (dequeue) {
                list_.remove(i - list_.begin()); //TODO: this certainly won't work
                _display->qlen--;
            }
            return true;
        }
        evl.unlock();

        if (!wait)
            return false;
        wait_for_more();
    }
    return false;
}

extern "C" int
XSelectInput(Display* /*display*/, Window w, long mask)
{
    auto window = ObjectManager::the().get_window(w);
    if (window.is_null())
        return BadWindow;
    window->event_mask(mask);
    return Success;
}

extern "C" int
XNextEvent(Display* display, XEvent* event)
{
    XFlush(display);
    Events::instance_for(display).wait_for_next(event);
    return Success;
}

extern "C" int
XFlush(Display* dpy)
{
    // We only have the "input buffer" to flush.
    size_t nbytes;
    ioctl(dpy->fd, FIONREAD, &nbytes);

    while (nbytes) {
        char dummy[16];
        int rd = read(dpy->fd, dummy, min(nbytes, sizeof(dummy)));
        if (rd > 0)
            nbytes -= rd;
    }

    return Success;
}