#include <AK/Atomic.h>
#include <AK/Format.h>

#include <LibGUI/Desktop.h>
#include <LibGfx/Color.h>

#include "Color.h"
#include "Lock.h"

#include <unistd.h>

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
}
}

static bool sThreads = false;
static AK::Atomic<int32_t> sOpenDisplays = 0;

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
//    if (sOpenDisplays != 0)
//        dbgln("libX11: warning: application opened more than one X display!");

    XLib::Display* display = new XLib::_XDisplay;
    memset(display, 0, sizeof(XLib::Display));

    int eventsPipe[2];
    pipe(eventsPipe);
    display->fd = eventsPipe[0];
    display->conn_checker = eventsPipe[1];

    // TODO: we need event loop

    set_display(display);
//    _x_init_atoms();
//    _x_init_font();
//    _x_init_events(display);
    sOpenDisplays++;
    return display;
}