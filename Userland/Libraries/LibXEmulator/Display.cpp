#include <AK/Atomic.h>
#include <AK/Format.h>

#include <LibGUI/Desktop.h>
#include <LibGfx/Color.h>
#include <LibGfx/Palette.h>
#include <LibGUI/Application.h>

#include "Color.h"
#include "Lock.h"
#include "Atom.h"
#undef max
#include "Font.h"
#include "Event.h"

#include <unistd.h>

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#include <X11/Xutil.h>
}
}

static bool sThreads = false;
static AK::Atomic<int32_t> sOpenDisplays = 0;
static RefPtr<GUI::Application> s_app;

static void
x_lock_display(XLib::Display* dpy)
{
    _XLockMutex(dpy->lock);
}

static void
x_unlock_display(XLib::Display* dpy)
{
    _XUnlockMutex(dpy->lock);
}

static void
set_display(XLib::Display* dpy)
{
    static XLib::Depth dlist[1];
    static XLib::Visual vlist[1];
    static XLib::Screen slist[1];
    static char vstring[] = "LibXEmulator";

    const auto& desktop = GUI::Desktop::the();

    memset(slist, 0, sizeof(XLib::Screen));

    dlist[0].depth      = 24;
    dlist[0].nvisuals   = 1;
    dlist[0].visuals    = vlist;

    vlist[0].ext_data     = NULL;
    vlist[0].visualid     = 0;
    vlist[0].c_class      = TrueColor;
    vlist[0].bits_per_rgb = dlist[0].depth;
    vlist[0].map_entries  = 256;
    _x_get_rgb_masks(&vlist[0]);

    const auto screenFrame = desktop.rect();
    slist[0].width       = screenFrame.width();
    slist[0].height      = screenFrame.height();
    slist[0].mwidth      = screenFrame.width() * 0.2646;
    slist[0].mheight     = screenFrame.height() * 0.2646;
    // TODO: get real mm!
    slist[0].ndepths     = 1;
    slist[0].depths      = dlist;
    slist[0].root_depth  = dlist[0].depth;
    slist[0].root_visual = vlist;
    slist[0].default_gc  = NULL;
    slist[0].cmap        = XCreateColormap(dpy, None, &vlist[0], AllocNone);
    slist[0].white_pixel = _x_rgb_to_pixel(Color(0xFF, 0xFF, 0xFF));
    slist[0].black_pixel = _x_rgb_to_pixel(Color(0, 0, 0));

    slist[0].display = dpy;
    slist[0].root = 100; /* arbitrary */

    dpy->ext_data            = NULL;
    dpy->proto_major_version = 11;
    dpy->proto_minor_version = 4;
    dpy->vendor              = vstring;
    dpy->display_name        = vstring;
    dpy->nscreens            = 1;
    dpy->screens             = slist;
    dpy->default_screen		 = 0;
    dpy->min_keycode		 = 8;
    dpy->max_keycode         = 255;
    dpy->max_request_size	 = 4096;
    dpy->bigreq_size		 = dpy->max_request_size;
    dpy->qlen                = 0;
    dpy->request			 = 1;
    dpy->head = dpy->tail    = NULL;
    dpy->qfree               = NULL;

    dpy->free_funcs = (XLib::_XFreeFuncRec *)Xcalloc(1, sizeof(XLib::_XFreeFuncRec));

    if (sThreads) {
        dpy->lock = (XLib::_XLockInfo*)calloc(1, sizeof(XLib::_XLockInfo));
        _XCreateMutex(dpy->lock);

        dpy->lock_fns = (XLib::_XLockPtrs*)calloc(1, sizeof(XLib::_XLockPtrs));
        dpy->lock_fns->lock_display = x_lock_display;
        dpy->lock_fns->unlock_display = x_unlock_display;
    }
}

extern "C" XLib::Display*
XLib::XOpenDisplay(const char*)
{
    if (sOpenDisplays != 0)
        dbgln("LibX11: warning: application opened more than one X display!");

    XLib::Display* display = new XLib::_XDisplay;
    memset(display, 0, sizeof(XLib::Display));

    int eventsPipe[2];
    pipe(eventsPipe);
    display->fd = eventsPipe[0];
    display->conn_checker = eventsPipe[1];

    s_app = MUST(GUI::Application::try_create(0, nullptr, Core::EventLoop::MakeInspectable::Yes));

    set_display(display);
    _x_init_atoms();
    _x_init_font();
    _x_init_events(display);
    sOpenDisplays++;
    return display;
}

extern "C" int
XLib::XCloseDisplay(Display* display)
{
    sOpenDisplays--;

//    _x_extensions_close(display);
    _x_finalize_events(display);
//    _x_finalize_font();

    close(display->fd);
    close(display->conn_checker);

    _XFreeMutex(display->lock);
    XFree(display->lock);
    XFree(display->lock_fns);
    XFree(display->free_funcs);
    delete display;
    return 0;
}

extern "C" int
XLib::XScreenNumberOfScreen(Screen* screen)
{
    for (int i = 0; i < screen->display->nscreens; i++) {
        if (&screen->display->screens[i] == screen)
            return i;
    }
    return -1;
}

extern "C" int
XLib::XFree(void *data)
{
    free(data);
    return 0;
}

static void
fill_visual_info(XLib::Visual* v, XLib::XVisualInfo* info)
{
    info->visual = v;
    info->visualid = info->visual->visualid;
    info->screen = 0;
    info->depth = info->visual->bits_per_rgb;
    info->c_class = info->visual->c_class;
    info->colormap_size = info->visual->map_entries;
    info->bits_per_rgb = info->visual->bits_per_rgb;
    info->red_mask = info->visual->red_mask;
    info->green_mask = info->visual->green_mask;
    info->blue_mask = info->visual->blue_mask;
}

extern "C" XLib::XVisualInfo*
XLib::XGetVisualInfo(Display *display, long vinfo_mask, XVisualInfo *vinfo_template, int *nitems_return)
{
    XVisualInfo* info = (XVisualInfo*)calloc(1, sizeof(XVisualInfo));
    fill_visual_info(DefaultVisual(display, 0), info);

    if (((vinfo_mask & VisualIDMask)
            && (vinfo_template->visualid != info->visualid))
        || ((vinfo_mask & VisualScreenMask)
            && (vinfo_template->screen != info->screen))
        || ((vinfo_mask & VisualDepthMask)
            && (vinfo_template->depth != info->depth))
        || ((vinfo_mask & VisualClassMask)
            && (vinfo_template->c_class != info->c_class))
        || ((vinfo_mask & VisualColormapSizeMask)
            && (vinfo_template->colormap_size != info->colormap_size))
        || ((vinfo_mask & VisualBitsPerRGBMask)
            && (vinfo_template->bits_per_rgb != info->bits_per_rgb))
        || ((vinfo_mask & VisualRedMaskMask)
            && (vinfo_template->red_mask != info->red_mask))
        || ((vinfo_mask & VisualGreenMaskMask)
            && (vinfo_template->green_mask != info->green_mask))
        || ((vinfo_mask & VisualBlueMaskMask)
            && (vinfo_template->blue_mask != info->blue_mask))
    ) {
        free(info);
        return NULL;
    }

    *nitems_return = 1;
    return info;
}