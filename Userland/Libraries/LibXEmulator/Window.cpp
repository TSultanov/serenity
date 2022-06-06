#include "ObjectManager.h"
#include "Drawing.h"
#include "XWindow.h"

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#include <X11/Xutil.h>
}
}

extern "C" XLib::Window
XLib::XCreateSimpleWindow(XLib::Display* display, XLib::Window parent, int x, int y, unsigned int width,
    unsigned int height, unsigned int border_width, unsigned long border, unsigned long background)
{
    XLib::XSetWindowAttributes attributes;
    attributes.border_pixel = border;
    attributes.background_pixel = background;
    return XCreateWindow(display, parent, x, y, width, height, border_width,
        CopyFromParent, CopyFromParent, CopyFromParent,
        CWBackPixel | CWBorderPixel, &attributes);
}

extern "C" XLib::Window
XLib::XCreateWindow(XLib::Display* display, XLib::Window parent, int x, int y, unsigned int w,
    unsigned int h, unsigned int /*border_width*/, int /*depth*/, unsigned int /*clazz*/,
    Visual* /*visual*/, unsigned long /*valueMask*/, XLib::XSetWindowAttributes* _attributes)
{
    XLib::XSetWindowAttributes attributes = {};
    if (_attributes)
        attributes = *_attributes;

    Gfx::IntRect frame(intrect_from_xrect(make_xrect(x, y, w, h)));

    auto window = XWindow::construct(display, frame);

    auto parent_window = ObjectManager::the().get_window(parent);

    if (parent_window.is_null()) {
        window->create_host_window();
        window->window()->move_to(x, y);
    } else {
        //window->view()->Hide();
        parent_window->add_child(window);

//        if (parent_window->event_mask() & SubstructureNotifyMask) { // TODO: what event should we pass?
//            XEvent event = {};
//            event.type = CreateNotify;
//            event.xcreatewindow.parent = parent;
//            event.xcreatewindow.window = window->id();
//            event.xcreatewindow.x = x;
//            event.xcreatewindow.y = y;
//            event.xcreatewindow.width = w;
//            event.xcreatewindow.height = h;
//            event.xcreatewindow.border_width = border_width;
//            _x_put_event(display, event);
//        }
    }

    //XChangeWindowAttributes(display, window->id(), valueMask, &attributes);
    return window->id();
}

extern "C" Status
XLib::XChangeWindowAttributes(XLib::Display */*display*/, XLib::Window w,
    unsigned long /*vmask*/, XLib::XSetWindowAttributes */*attr*/)
{
    XWindow* window = ObjectManager::the().get_window(w);
    if (!window)
        return BadWindow;

    //TODO: implement the attributes

    return Success;
}