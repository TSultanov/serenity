#include <AK/Format.h>

namespace XLib {
extern "C" {
#define register
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#include <X11/Xutil.h>
#include <X11/Xresource.h>
#undef register
}
}

using namespace XLib;

#define UNIMPLEMENTED() dbgln("Stub: {}", __func__)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-result"

extern "C" {

int XGrabServer(Display* display)
{
    // Not needed.
    return Success;
}

int XUngrabServer(Display* display)
{
    // Not needed.
    return Success;
}

int XChangePointerControl(Display* dpy,
    Bool do_acc, Bool do_thresh, int acc_numerator, int acc_denominator, int threshold)
{
    UNIMPLEMENTED();
    return 0;
}

XTimeCoord*
XGetMotionEvents(Display* display, Window w, XLib::Time start, XLib::Time stop, int* nevents_return)
{
    UNIMPLEMENTED();
    *nevents_return = 0;
    return NULL;
}

int XAllowEvents(Display* display, int event_mode, XLib::Time time)
{
    // We never freeze events, so we have nothing to unfreeze.
    return Success;
}

Status
XAddConnectionWatch(Display* display, XConnectionWatchProc procedure, XPointer client_data)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

void XRemoveConnectionWatch(Display* display, XConnectionWatchProc procedure, XPointer client_data)
{
    UNIMPLEMENTED();
}

void XProcessInternalConnection(Display* display, int fd)
{
    UNIMPLEMENTED();
}

XHostAddress*
XListHosts(Display* display, int* nhosts_return, Bool* state_return)
{
    UNIMPLEMENTED();
    return NULL;
}

void XSetWMClientMachine(Display* display, Window w, XTextProperty* text_prop)
{
    UNIMPLEMENTED();
}

void XSetWMSizeHints(Display* display, Window w, XSizeHints* hints, Atom property)
{
    UNIMPLEMENTED();
}

XWMHints*
XGetWMHints(Display* display, Window w)
{
    return NULL;
}

Status
XGetTransientForHint(Display* display, Window w, Window* prop_window_return)
{
    *prop_window_return = None;
    UNIMPLEMENTED();
    return BadImplementation;
}

Colormap*
XListInstalledColormaps(Display* display, Window w, int* num_return)
{
    UNIMPLEMENTED();
    return NULL;
}

int XSetWindowColormap(Display* display, Window w, Colormap colormap)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

Status
XGetWMColormapWindows(Display* display, Window w, Window** windows_return,
    int* count_return)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

Status
XSetWMColormapWindows(Display* display, Window w,
    Window* colormap_windows, int count)
{
    UNIMPLEMENTED();
    return 0;
}

int XSetWMHints(Display* display, Window w, XWMHints* wm_hints)
{
    UNIMPLEMENTED();
    return 0;
}

int XRefreshKeyboardMapping(XMappingEvent* event_map)
{
    UNIMPLEMENTED();
    return 0;
}

VisualID
XVisualIDFromVisual(Visual* visual)
{
    UNIMPLEMENTED();
    return 0;
}

int XSetClassHint(Display* display, Window w, XClassHint* class_hints)
{
    UNIMPLEMENTED();
    return 0;
}

int XGetClassHint(Display* display, Window w, XClassHint* class_hints_return)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XSetStipple(Display* display, GC gc, Pixmap stipple)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XSetTile(Display* display, GC gc, Pixmap tile)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XSetPlaneMask(Display* display, GC gc, Pixmap planeMask)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XSetTSOrigin(Display* display, GC gc, int x, int y)
{
    return BadImplementation;
}

int XSetIconName(Display* display, Window w, const char * icon_name)
{
    return BadImplementation;
}

void XSetWMIconName(Display* display, Window w, XTextProperty* icon_name)
{
}

int XGetWMIconName(Display* display, Window w, XTextProperty* icon_name_return)
{
    return BadImplementation;
}

int XGetWMClientMachine(Display* display, Window w, XTextProperty* client_machine_return)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XSetIconSizes(Display* display, Window w, XIconSize* size_list, int count)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int (*XSynchronize(Display*, Bool))(Display*)
{
    UNIMPLEMENTED();
    return NULL;
}

int XSetCommand(Display* display, Window w, char** argv, int argc)
{
    UNIMPLEMENTED();
    return 0;
}

XErrorHandler
XSetErrorHandler(XErrorHandler handler)
{
    return NULL;
}

XIOErrorHandler
XSetIOErrorHandler(XIOErrorHandler handler)
{
    return NULL;
}

int XResetScreenSaver(Display* display)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XForceScreenSaver(Display* display, int)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XGetScreenSaver(Display* display, int* timeout_return, int* interval_return, int* prefer_blanking_return,
    int* allow_exposures_return)
{
    UNIMPLEMENTED();
    *timeout_return = 0;
    *interval_return = 0;
    *prefer_blanking_return = 0;
    *allow_exposures_return = 0;
    return BadImplementation;
}

int XSetScreenSaver(Display* display, int timeout, int interval, int prefer_blanking, int allow_exposures)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XSetWindowBorderPixmap(Display* display, Window w, Pixmap border_pixmap)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XSetWindowBackgroundPixmap(Display* display, Window w, Pixmap background_pixmap)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XWarpPointer(Display* display, Window src_w, Window dest_w,
    int src_x, int src_y, unsigned int src_width,
    unsigned int src_height, int dest_x, int dest_y)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XGetPointerControl(Display* display,
    int* accel_numerator_return, int* accel_denominator_return, int* threshold_return)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

char* XSetLocaleModifiers(const char * modifier_list)
{
    UNIMPLEMENTED();
    return NULL;
}

int XGetErrorDatabaseText(Display* dpy, const char* name,
	const char* message, const char* default_string, char* buffer_return, int length)
{
    UNIMPLEMENTED();
    strlcpy(buffer_return, default_string, length);
    return 0;
}

int XGetErrorText(Display* dpy, int code, char* buffer_return, int length)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

char* XGetDefault(Display* display, const char* program, const char* option)
{
    UNIMPLEMENTED();
    return NULL;
}

int XGrabButton(Display* display, unsigned int button, unsigned int modifiers, Window grab_window,
    Bool owner_events, unsigned int event_mask, int pointer_mode, int keyboard_mode, Window confine_to, Cursor cursor)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XUngrabButton(Display* display, unsigned int button, unsigned int modifiers, Window grab_window)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

Status
XGetRGBColormaps(Display* display, Window w, XStandardColormap** std_colormap_return, int* count_return, Atom property)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

void XSetRGBColormaps(Display* display, Window w, XStandardColormap* std_colormap, int count, Atom property)
{
    UNIMPLEMENTED();
}

int XKillClient(Display* display, XID resource)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XSetCloseDownMode(Display* display, int close_mode)
{
    return BadImplementation;
}

GContext
XGContextFromGC(GC gc)
{
    UNIMPLEMENTED();
    return 0;
}

int XStoreBytes(Display* display, const char * bytes, int nbytes)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XStoreBuffer(Display* display, const char * bytes, int nbytes, int buffer)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

char* XFetchBytes(Display* display, int* nbytes_return)
{
    UNIMPLEMENTED();
    return NULL;
}

char* XFetchBuffer(Display* display, int* nbytes_return, int buffer)
{
    UNIMPLEMENTED();
    return NULL;
}

int XRotateBuffers(Display* display, int rotate)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

XOM XOMOfOC(XOC oc)
{
    UNIMPLEMENTED();
    return NULL;
}

char* XSetOCValues(XOC oc, ...)
{
    UNIMPLEMENTED();
    return NULL;
}

char* XGetOCValues(XOC oc, ...)
{
    UNIMPLEMENTED();
    return NULL;
}

char* XGetOMValues(XOM om, ...)
{
    UNIMPLEMENTED();
    return NULL;
}

int XChangeSaveSet(Display* display, Window w, int change_mode)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XAddToSaveSet(Display* display, Window w)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XRemoveFromSaveSet(Display* display, Window w)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XGetPointerMapping(Display* display, unsigned char* map_return, int nmap)
{
    UNIMPLEMENTED();
    // Assume we have 3 buttons for now?
    return 3;
}

int XRestackWindows(Display* display, Window windows[], int nwindows)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

extern "C" int
XBell(Display* dpy, int percent)
{
    UNIMPLEMENTED();
    return 0;
}


extern "C" XIM
XOpenIM(Display* dpy,
    struct _XrmHashBucketRec* rdb, char* res_name, char* res_class)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" Display*
XDisplayOfIM(XIM im)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" char*
XLocaleOfIM(XIM im)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" char*
XGetIMValues(XIM im, ...)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" char*
XSetIMValues(XIM im, ...)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" Bool
XRegisterIMInstantiateCallback(Display* dpy,
    struct _XrmHashBucketRec* rdb, char* res_name, char* res_class,
    XIDProc callback, XPointer client_data)
{
    UNIMPLEMENTED();
    return False;
}

extern "C" Bool
XUnregisterIMInstantiateCallback(Display* dpy,
    struct _XrmHashBucketRec* rdb, char* res_name, char* res_class,
    XIDProc callback, XPointer client_data)
{
    UNIMPLEMENTED();
    return False;
}

extern "C" Status
XCloseIM(XIM xim)
{
    UNIMPLEMENTED();
    return 0;
}

extern "C" XIC
XCreateIC(XIM xim, ...)
{
    UNIMPLEMENTED();
    // Unimplemented.
    return NULL;
}

extern "C" XIM
XIMOfIC(XIC ic)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" char*
XmbResetIC(XIC ic)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" void
XDestroyIC(XIC ic)
{
    UNIMPLEMENTED();
}

extern "C" char*
XSetICValues(XIC ic, ...)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" char*
XGetICValues(XIC ic, ...)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" void
XSetICFocus(XIC ic)
{
    UNIMPLEMENTED();
}

extern "C" void
XUnsetICFocus(XIC ic)
{
    UNIMPLEMENTED();
}

extern "C" Bool
XFilterEvent(XEvent *event, Window window)
{
    UNIMPLEMENTED();
    return 0;
}

extern "C" int
Xutf8LookupString(XIC ic, XKeyPressedEvent* event,
    char* buffer_return, int bytes_buffer, KeySym* keysym_return, Status* status_return)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

extern "C" XVaNestedList
XVaCreateNestedList(int dummy, ...)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" Bool
XCheckIfEvent(Display* display, XEvent* event_return,
    Bool (*predicate)(Display*, XEvent*, XPointer), XPointer arg)
{
    UNIMPLEMENTED();
    return False;
}

extern "C" int
XConvertSelection(Display* display, Atom selection, Atom target,
    Atom property, Window requestor, XLib::Time time)
{
    UNIMPLEMENTED();
    return 1;
}

extern "C" void
XmbSetWMProperties(Display* display, Window w,
	const char* window_name, const char* icon_name, char** argv, int argc,
    XSizeHints* normal_hints, XWMHints* wm_hints, XClassHint* class_hints)
{
    UNIMPLEMENTED();
}

extern "C" Bool
XQueryPointer(Display *display, Window w, Window* root_return,
    Window* child_return, int* root_x_return, int* root_y_return,
    int* win_x_return, int *win_y_return,
    unsigned int* mask_return)
{
    UNIMPLEMENTED();
    return False;
}

extern "C" int
XDefineCursor(Display *display, Window w, Cursor cursor)
{
    UNIMPLEMENTED();
    return Success;
}

extern "C" int
XGetWindowProperty(Display* dpy, Window w, Atom property,
    long long_offset, long long_length, Bool del, Atom req_type,
    Atom* actual_type_return, int* actual_format_return,
    unsigned long* nitems_return, unsigned long* bytes_after_return, unsigned char** prop_return)
{
    // Always initialize return values, same as the real Xlib.
    *actual_type_return = 0;
    *actual_format_return = 0;
    *nitems_return = 0;
    *bytes_after_return = 0;
    *prop_return = NULL;
    UNIMPLEMENTED();

    return Success;
}

extern "C" Window
XGetSelectionOwner(Display* display, Atom selection)
{
    UNIMPLEMENTED();
    return None;
}

extern "C" Bool
XIfEvent(Display* display, XEvent* event_return,
    Bool (*predicate)(Display*, XEvent*, XPointer), XPointer arg)
{
    UNIMPLEMENTED();
    return Success;
}

extern "C" Status
XFreeColormap(Display* display, Colormap colormap)
{
    return Success;
}

extern "C" int
XSetSelectionOwner(Display* display, Atom selection, Window owner, XLib::Time time)
{
    UNIMPLEMENTED();
    return BadImplementation;
}
}
#pragma GCC diagnostic pop
