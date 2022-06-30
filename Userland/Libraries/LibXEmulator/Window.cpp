#include "Drawing.h"
#include "Event.h"
#include "ObjectManager.h"
#include "X11/Xatom.h"
#include "XWindow.h"
#undef None
#include <LibGUI/Application.h>
#include <LibGfx/Palette.h>

namespace XLib {
extern "C" {
#define register
#include <X11/Xlib.h>
#define Bool int
#include <X11/Xlibint.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
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

extern "C" int
XLib::XSetInputFocus(Display* /*display*/, Window focus, int /*revert_to*/, Time time)
{
    auto window = ObjectManager::the().get_window(focus);
    if (focus == PointerRoot)
        window = nullptr;
    if (window && !window->widget()->window())
        return BadWindow;

    if (time > _x_current_time())
        return Success;
//    if (window == Drawables::focused())
//        return Success;

    const bool defocus = window.is_null();

    window->widget()->set_focus(defocus);
    return Success;
}

extern "C" Status
XLib::XGetGeometry(Display* display, Drawable d, Window* root_return,
    int* x_return, int* y_return, unsigned int* width_return,
    unsigned int* height_return, unsigned int* border_width_return,
    unsigned int* depth_return)
{
    XWindowAttributes window_attributes;
    Status status = XGetWindowAttributes(display, d, &window_attributes);
    if (status != 1)
        return status;
    if (root_return)
        *root_return = window_attributes.root;
    if (x_return)
        *x_return = window_attributes.x;
    if (y_return)
        *y_return = window_attributes.y;
    if (width_return)
        *width_return = window_attributes.width;
    if (height_return)
        *height_return = window_attributes.height;
    if (border_width_return)
        *border_width_return = window_attributes.border_width;
    if (depth_return)
        *depth_return = window_attributes.depth;
    return 1;
}

extern "C" int
XLib::XWithdrawWindow(Display *display, Window w, int /*screen*/)
{
    XUnmapWindow(display, w);
    return 1;
}

extern "C" int
XLib::XUnmapWindow(Display *display, Window w)
{
    auto window = ObjectManager::the().get_window(w);
    if (!window)
        return BadWindow;

    window->widget()->window()->hide();

    XWindow* parent = window->parent_window();
const bool selfNotify = (window->event_mask() & StructureNotifyMask);
    if (selfNotify || (parent && parent->event_mask() & SubstructureNotifyMask)) {
        XEvent event = {};
        event.type = UnmapNotify;
        event.xunmap.event = selfNotify ? window->id() : parent->id();
        event.xunmap.window = window->id();
        _x_put_event(display, event);
    }

    return Success;
}

extern "C" int
XLib::XGetWindowAttributes(Display* display, Window w,
    XWindowAttributes* window_attributes_return)
{
    auto window = ObjectManager::the().get_window(w);
    if (window.is_null())
        return 0;

    memset(window_attributes_return, 0, sizeof(XWindowAttributes));

    window_attributes_return->root = DefaultRootWindow(display);
    window_attributes_return->screen = &display->screens[0];
    // TODO: Not necessarily correct for pixmaps!
    window_attributes_return->visual = window_attributes_return->screen->root_visual;
    window_attributes_return->c_class = window_attributes_return->visual->c_class;
    window_attributes_return->depth = window_attributes_return->screen->depths[0].depth;

    Gfx::IntRect frame;
    bool hidden = true, minimized = false;
    frame = window->widget()->window()->rect();
    hidden = !window->widget()->window()->is_visible();
    //minimized = window->widget()->window()->mini;
    minimized = false;

    window_attributes_return->x = frame.top_left().x();
    window_attributes_return->y = frame.top_left().y();
    window_attributes_return->width = frame.width();
    window_attributes_return->height = frame.height();
    window_attributes_return->border_width = 1;
    window_attributes_return->your_event_mask = window->event_mask();
    window_attributes_return->all_event_masks = window->event_mask();
    window_attributes_return->map_state =
        minimized ? IsUnviewable : (hidden ? IsUnmapped : IsViewable);

    return 1;
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


extern "C" XSizeHints*
XAllocSizeHints()
{
    return (XSizeHints*)malloc(sizeof(XSizeHints));
}

extern "C" int
XGetNormalHints(Display* display, Window w, XSizeHints* hints)
{
    UNIMPLEMENTED();
    return Success;
}

extern "C" int
XSetNormalHints(Display* display, Window w, XSizeHints* hints)
{
    UNIMPLEMENTED();
    return Success;
}

extern "C" Status
XSetWMProtocols(Display* display, Window w, Atom* protocols, int count)
{
    UNIMPLEMENTED();
    return Success;
}

extern "C" Status
XGetWMNormalHints(Display* display, Window w, XSizeHints* hints_return, long* supplied_return)
{
    UNIMPLEMENTED();
    return 0;
}

extern "C" void
XSetWMNormalHints(Display* display, Window w, XSizeHints* hints)
{
    XSetNormalHints(display, w, hints);
}

extern "C" int
XSetStandardProperties(Display* display, Window w,
	const char* window_name, const char* icon_name, Pixmap icon_pixmap,
    char** argv, int argc, XSizeHints* hints)
{
    UNIMPLEMENTED();
    return Success;
}

extern "C" void
XSetWMProperties(Display* display, Window w, XTextProperty* window_name, XTextProperty* icon_name,
    char** argv, int argc, XSizeHints* normal_hints, XWMHints* wm_hints, XClassHint* class_hints)
{
    if (window_name)
        XSetWMName(display, w, window_name);
    if (icon_name)
        XSetWMIconName(display, w, icon_name);
    if (normal_hints)
        XSetWMNormalHints(display, w, normal_hints);
    if (wm_hints)
        XSetWMHints(display, w, wm_hints);
    if (class_hints)
        XSetClassHint(display, w, class_hints);
}

extern "C" XWMHints*
XAllocWMHints(void)
{
    return (XWMHints*)malloc(sizeof(XWMHints));
}

extern "C" Status
XGetWMName(Display* display, Window w, XTextProperty* name_return)
{
    UNIMPLEMENTED();
    return Success;
}

extern "C" void
XSetWMName(Display* display, Window w, XTextProperty* name)
{
    UNIMPLEMENTED();
}

extern "C" int
XFetchName(Display* display, Window w, char** window_name_return)
{
    UNIMPLEMENTED();
    return BadWindow;
}

extern "C" int
XLib::XStoreName(Display* display, Window w, const char* wname)
{
    UNIMPLEMENTED();
    return 0;
}

extern "C" int
XSetWindowBackground(Display *display, Window w, unsigned long bg)
{
    UNIMPLEMENTED();
    return Success;
}

extern "C" int
XSetWindowBorder(Display* display, Window w, unsigned long border_pixel)
{
    UNIMPLEMENTED();
    return Success;
}

extern "C" int
XClearWindow(Display *display, Window w)
{
    UNIMPLEMENTED();
    return Success;
}

extern "C" Status
XReconfigureWMWindow(Display* display, Window w, int screen_number,
    unsigned int value_mask, XWindowChanges* values)
{
    return XConfigureWindow(display, w, value_mask, values);
}

extern "C" int
XMoveWindow(Display* display, Window window, int x, int y)
{
    XWindowChanges changes;
    changes.x = x;
    changes.y = y;
    return XConfigureWindow(display, window, CWX | CWY, &changes);
}

extern "C" int
XResizeWindow(Display* display, Window window, unsigned int width, unsigned int height)
{
    XWindowChanges changes;
    changes.width = width;
    changes.height = height;
    return XConfigureWindow(display, window, CWWidth | CWHeight, &changes);
}

extern "C" int
XRaiseWindow(Display* display, Window w)
{
    XWindowChanges changes;
    changes.stack_mode = Above;
    return XConfigureWindow(display, w, CWStackMode, &changes);
}

extern "C" int
XLowerWindow(Display* display, Window w)
{
    XWindowChanges changes;
    changes.stack_mode = Below;
    return XConfigureWindow(display, w, CWStackMode, &changes);
}

extern "C" int
XQueryTree(Display* display, Window w, Window* root_return,
    Window* parent_return, Window** children_return, unsigned int* nchildren_return)
{
    UNIMPLEMENTED();
    return Success;
}

extern "C" int
XConfigureWindow(Display* display, Window w, unsigned int value_mask, XWindowChanges* values)
{
    UNIMPLEMENTED();
    return Success;
}


extern "C" int
XLib::XIconifyWindow(Display *display, Window w, int screen)
{
    UNIMPLEMENTED();
    return BadValue;
}

extern "C" int
XSetTransientForHint(Display* display, Window w, Window prop_w)
{
    UNIMPLEMENTED();
    return Success;
}

extern "C" int
XReparentWindow(Display* dpy, Window w, Window nP, int x, int y)
{
    UNIMPLEMENTED();
    return Success;
}

#pragma GCC diagnostic pop
