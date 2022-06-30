#include "ObjectManager.h"
#include "Drawing.h"
#include "XWindow.h"
#include "Event.h"
#undef None
#include <LibGUI/Application.h>
#include <LibGfx/Palette.h>

namespace XLib {
extern "C" {
#define register
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#include <X11/Xutil.h>
#undef register
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

//    auto app = GUI::Application::the();

    Gfx::IntRect frame(intrect_from_xrect(make_xrect(x, y, w, h)));

    auto parent_window = ObjectManager::the().get_window(parent);

    RefPtr<XWindow> xwindow;

    if(parent_window.is_null())
    {
        auto host_window = MUST(GUI::Window::try_create());
        xwindow = MUST(XWindow::try_create(display, host_window, frame));
        host_window->set_main_widget(xwindow->widget());
        host_window->resize(w, h);
    }
    else
    {
        xwindow = MUST(XWindow::try_create(display, parent_window->widget()->window(), frame));
        xwindow->widget()->resize(w, h);
        parent_window->add_child(*xwindow);
    }

    {
        //window->view()->Hide();

        if (!parent_window.is_null() && (parent_window->event_mask() & SubstructureNotifyMask)) { // TODO: what event should we pass?
            XEvent event = {};
            event.type = CreateNotify;
            event.xcreatewindow.parent = parent;
            event.xcreatewindow.window = xwindow->id();
            event.xcreatewindow.x = x;
            event.xcreatewindow.y = y;
            event.xcreatewindow.width = w;
            event.xcreatewindow.height = h;
            //event.xcreatewindow.border_width = border_width;
            _x_put_event(display, event);
        }
    }

    //XChangeWindowAttributes(display, window->id(), valueMask, &attributes);
    return xwindow->id();
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

extern "C" int
XLib::XMapWindow(XLib::Display* display, XLib::Window w)
{
    auto window = ObjectManager::the().get_window(w);
    if (window.is_null())
        return BadWindow;

    if (window->widget()->window()) {
        dbgln("Has parent window");
        window->widget()->window()->show();
    } else {
        dbgln("Doesn't have parent window");
        window->widget()->set_visible(true);
    }

    auto parent = window->parent_window();
    const bool selfNotify = (window->event_mask() & StructureNotifyMask);
    if (selfNotify || (parent && parent->event_mask() & SubstructureNotifyMask)) {
        XEvent event = {};
        event.type = MapNotify;
        event.xmap.event = selfNotify ? window->id() : parent->id();
        event.xmap.window = window->id();
        _x_put_event(display, event);
    }

    return Success;
}

extern "C" int
XLib::XDestroyWindow(Display */*display*/, Window w)
{
    auto window = ObjectManager::the().get_window(w);
    if (window.is_null())
        return BadWindow;

    ObjectManager::the().remove_window(w);
    return Success;
}

extern "C" int
XLib::XClearArea(Display */*display*/, Window w,
    int /*x*/, int /*y*/, unsigned int /*width*/, unsigned int /*height*/, Bool /*exposures*/)
{
    auto window = ObjectManager::the().get_window(w);
    if (window.is_null())
        return BadWindow;

//    Gfx::IntRect rect(intrect_from_xrect(make_xrect(x, y, width, height)));
//    //window->draw_border(rect); // FIXME
//    if (exposures && window->widget()->window()) {
//        window->widget()-;
//    }
    // TODO: figure out how to do this
    dbgln("LibXEmulator: XClearArea stub");
    return Success;
}

extern "C" XLib::XClassHint*
XLib::XAllocClassHint(void)
{
    return (XClassHint*)malloc(sizeof(XClassHint));
}

// stubs
#define UNIMPLEMENTED() dbgln("Stub: {}", __func__)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-result"

using namespace XLib;

extern "C" int
XGrabPointer(Display* display, Window grab_w, Bool owner_events, unsigned int event_mask,
    int pointer_mode, int keyboard_mode, Window confine_to_w, Cursor cursor, XLib::Time time)
{
    UNIMPLEMENTED();
    return GrabSuccess;
}

extern "C" int
XUngrabPointer(Display* display, XLib::Time time)
{
    UNIMPLEMENTED();
    return GrabSuccess;
}

extern "C" int
XMoveResizeWindow(Display *display, Window w,
    int x, int y, unsigned int width, unsigned int height)
{
    UNIMPLEMENTED();
    return Success;
}


extern "C" Bool
XLib::XTranslateCoordinates(Display* display,
    Window src_w, Window dest_w, int src_x, int src_y,
    int* dest_x_return, int* dest_y_return, Window* child_return)
{
    UNIMPLEMENTED();
    return True;
}

#pragma GCC diagnostic pop
