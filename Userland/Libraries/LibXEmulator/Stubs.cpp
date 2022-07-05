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

int XLib::XGrabServer(Display* display)
{
    // Not needed.
    return Success;
}

int XLib::XUngrabServer(Display* display)
{
    // Not needed.
    return Success;
}

int XLib::XChangePointerControl(Display* dpy,
    Bool do_acc, Bool do_thresh, int acc_numerator, int acc_denominator, int threshold)
{
    UNIMPLEMENTED();
    return 0;
}

XTimeCoord*
XLib::XGetMotionEvents(Display* display, Window w, XLib::Time start, XLib::Time stop, int* nevents_return)
{
    UNIMPLEMENTED();
    *nevents_return = 0;
    return NULL;
}

int XLib::XAllowEvents(Display* display, int event_mode, XLib::Time time)
{
    // We never freeze events, so we have nothing to unfreeze.
    return Success;
}

Status
XLib::XAddConnectionWatch(Display* display, XConnectionWatchProc procedure, XPointer client_data)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

void XLib::XRemoveConnectionWatch(Display* display, XConnectionWatchProc procedure, XPointer client_data)
{
    UNIMPLEMENTED();
}

void XLib::XProcessInternalConnection(Display* display, int fd)
{
    UNIMPLEMENTED();
}

XHostAddress*
XLib::XListHosts(Display* display, int* nhosts_return, Bool* state_return)
{
    UNIMPLEMENTED();
    return NULL;
}

void XLib::XSetWMClientMachine(Display* display, Window w, XTextProperty* text_prop)
{
    UNIMPLEMENTED();
}

void XLib::XSetWMSizeHints(Display* display, Window w, XSizeHints* hints, Atom property)
{
    UNIMPLEMENTED();
}

XWMHints*
XLib::XGetWMHints(Display* display, Window w)
{
    return NULL;
}

Status
XLib::XGetTransientForHint(Display* display, Window w, Window* prop_window_return)
{
    *prop_window_return = None;
    UNIMPLEMENTED();
    return BadImplementation;
}

Colormap*
XLib::XListInstalledColormaps(Display* display, Window w, int* num_return)
{
    UNIMPLEMENTED();
    return NULL;
}

int XLib::XSetWindowColormap(Display* display, Window w, Colormap colormap)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

Status
XLib::XGetWMColormapWindows(Display* display, Window w, Window** windows_return,
    int* count_return)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

Status
XLib::XSetWMColormapWindows(Display* display, Window w,
    Window* colormap_windows, int count)
{
    UNIMPLEMENTED();
    return 0;
}

int XLib::XSetWMHints(Display* display, Window w, XWMHints* wm_hints)
{
    UNIMPLEMENTED();
    return 0;
}

int XLib::XRefreshKeyboardMapping(XMappingEvent* event_map)
{
    UNIMPLEMENTED();
    return 0;
}

VisualID
XLib::XVisualIDFromVisual(Visual* visual)
{
    UNIMPLEMENTED();
    return 0;
}

int XLib::XSetClassHint(Display* display, Window w, XClassHint* class_hints)
{
    UNIMPLEMENTED();
    return 0;
}

int XLib::XGetClassHint(Display* display, Window w, XClassHint* class_hints_return)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XLib::XSetStipple(Display* display, GC gc, Pixmap stipple)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XLib::XSetTile(Display* display, GC gc, Pixmap tile)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XLib::XSetPlaneMask(Display* display, GC gc, Pixmap planeMask)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XLib::XSetTSOrigin(Display* display, GC gc, int x, int y)
{
    return BadImplementation;
}

int XLib::XSetIconName(Display* display, Window w, const char * icon_name)
{
    return BadImplementation;
}

void XLib::XSetWMIconName(Display* display, Window w, XTextProperty* icon_name)
{
}

int XLib::XGetWMIconName(Display* display, Window w, XTextProperty* icon_name_return)
{
    return BadImplementation;
}

int XLib::XGetWMClientMachine(Display* display, Window w, XTextProperty* client_machine_return)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XLib::XSetIconSizes(Display* display, Window w, XIconSize* size_list, int count)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int (*XLib::XSynchronize(Display*, Bool))(Display*)
{
    UNIMPLEMENTED();
    return NULL;
}

int XLib::XSetCommand(Display* display, Window w, char** argv, int argc)
{
    UNIMPLEMENTED();
    return 0;
}

XErrorHandler
XLib::XSetErrorHandler(XErrorHandler handler)
{
    return NULL;
}

XIOErrorHandler
XLib::XSetIOErrorHandler(XIOErrorHandler handler)
{
    return NULL;
}

int XLib::XResetScreenSaver(Display* display)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XLib::XForceScreenSaver(Display* display, int)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XLib::XGetScreenSaver(Display* display, int* timeout_return, int* interval_return, int* prefer_blanking_return,
    int* allow_exposures_return)
{
    UNIMPLEMENTED();
    *timeout_return = 0;
    *interval_return = 0;
    *prefer_blanking_return = 0;
    *allow_exposures_return = 0;
    return BadImplementation;
}

int XLib::XSetScreenSaver(Display* display, int timeout, int interval, int prefer_blanking, int allow_exposures)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XLib::XSetWindowBorderPixmap(Display* display, Window w, Pixmap border_pixmap)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XLib::XSetWindowBackgroundPixmap(Display* display, Window w, Pixmap background_pixmap)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XLib::XWarpPointer(Display* display, Window src_w, Window dest_w,
    int src_x, int src_y, unsigned int src_width,
    unsigned int src_height, int dest_x, int dest_y)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XLib::XGetPointerControl(Display* display,
    int* accel_numerator_return, int* accel_denominator_return, int* threshold_return)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

char* XLib::XSetLocaleModifiers(const char * modifier_list)
{
    UNIMPLEMENTED();
    return NULL;
}

int XLib::XGetErrorDatabaseText(Display* dpy, const char* name,
	const char* message, const char* default_string, char* buffer_return, int length)
{
    UNIMPLEMENTED();
    strlcpy(buffer_return, default_string, length);
    return 0;
}

int XLib::XGetErrorText(Display* dpy, int code, char* buffer_return, int length)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

char* XLib::XGetDefault(Display* display, const char* program, const char* option)
{
    UNIMPLEMENTED();
    return NULL;
}

int XLib::XGrabButton(Display* display, unsigned int button, unsigned int modifiers, Window grab_window,
    Bool owner_events, unsigned int event_mask, int pointer_mode, int keyboard_mode, Window confine_to, Cursor cursor)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XLib::XUngrabButton(Display* display, unsigned int button, unsigned int modifiers, Window grab_window)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

Status
XLib::XGetRGBColormaps(Display* display, Window w, XStandardColormap** std_colormap_return, int* count_return, Atom property)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

void XLib::XSetRGBColormaps(Display* display, Window w, XStandardColormap* std_colormap, int count, Atom property)
{
    UNIMPLEMENTED();
}

int XLib::XKillClient(Display* display, XID resource)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XLib::XSetCloseDownMode(Display* display, int close_mode)
{
    return BadImplementation;
}

GContext
XLib::XGContextFromGC(GC gc)
{
    UNIMPLEMENTED();
    return 0;
}

int XLib::XStoreBytes(Display* display, const char * bytes, int nbytes)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XLib::XStoreBuffer(Display* display, const char * bytes, int nbytes, int buffer)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

char* XLib::XFetchBytes(Display* display, int* nbytes_return)
{
    UNIMPLEMENTED();
    return NULL;
}

char* XLib::XFetchBuffer(Display* display, int* nbytes_return, int buffer)
{
    UNIMPLEMENTED();
    return NULL;
}

int XLib::XRotateBuffers(Display* display, int rotate)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

XOM XLib::XOMOfOC(XOC oc)
{
    UNIMPLEMENTED();
    return NULL;
}

char* XLib::XSetOCValues(XOC oc, ...)
{
    UNIMPLEMENTED();
    return NULL;
}

char* XLib::XGetOCValues(XOC oc, ...)
{
    UNIMPLEMENTED();
    return NULL;
}

char* XLib::XGetOMValues(XOM om, ...)
{
    UNIMPLEMENTED();
    return NULL;
}

int XLib::XChangeSaveSet(Display* display, Window w, int change_mode)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XLib::XAddToSaveSet(Display* display, Window w)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XLib::XRemoveFromSaveSet(Display* display, Window w)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

int XLib::XGetPointerMapping(Display* display, unsigned char* map_return, int nmap)
{
    UNIMPLEMENTED();
    // Assume we have 3 buttons for now?
    return 3;
}

int XLib::XRestackWindows(Display* display, Window windows[], int nwindows)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

extern "C" int
XLib::XBell(Display* dpy, int percent)
{
    UNIMPLEMENTED();
    return 0;
}


extern "C" XIM
XLib::XOpenIM(Display* dpy,
    struct _XrmHashBucketRec* rdb, char* res_name, char* res_class)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" Display*
XLib::XDisplayOfIM(XIM im)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" char*
XLib::XLocaleOfIM(XIM im)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" char*
XLib::XGetIMValues(XIM im, ...)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" char*
XLib::XSetIMValues(XIM im, ...)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" Bool
XLib::XRegisterIMInstantiateCallback(Display* dpy,
    struct _XrmHashBucketRec* rdb, char* res_name, char* res_class,
    XIDProc callback, XPointer client_data)
{
    UNIMPLEMENTED();
    return False;
}

extern "C" Bool
XLib::XUnregisterIMInstantiateCallback(Display* dpy,
    struct _XrmHashBucketRec* rdb, char* res_name, char* res_class,
    XIDProc callback, XPointer client_data)
{
    UNIMPLEMENTED();
    return False;
}

extern "C" Status
XLib::XCloseIM(XIM xim)
{
    UNIMPLEMENTED();
    return 0;
}

extern "C" XIC
XLib::XCreateIC(XIM xim, ...)
{
    UNIMPLEMENTED();
    // Unimplemented.
    return NULL;
}

extern "C" XIM
XLib::XIMOfIC(XIC ic)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" char*
XLib::XmbResetIC(XIC ic)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" void
XLib::XDestroyIC(XIC ic)
{
    UNIMPLEMENTED();
}

extern "C" char*
XLib::XSetICValues(XIC ic, ...)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" char*
XLib::XGetICValues(XIC ic, ...)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" void
XLib::XSetICFocus(XIC ic)
{
    UNIMPLEMENTED();
}

extern "C" void
XLib::XUnsetICFocus(XIC ic)
{
    UNIMPLEMENTED();
}

extern "C" Bool
XLib::XFilterEvent(XEvent *event, Window window)
{
    UNIMPLEMENTED();
    return 0;
}

extern "C" int
XLib::Xutf8LookupString(XIC ic, XKeyPressedEvent* event,
    char* buffer_return, int bytes_buffer, KeySym* keysym_return, Status* status_return)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

extern "C" XVaNestedList
XLib::XVaCreateNestedList(int dummy, ...)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" Bool
XLib::XCheckIfEvent(Display* display, XEvent* event_return,
    Bool (*predicate)(Display*, XEvent*, XPointer), XPointer arg)
{
    UNIMPLEMENTED();
    return False;
}

extern "C" int
XLib::XConvertSelection(Display* display, Atom selection, Atom target,
    Atom property, Window requestor, XLib::Time time)
{
    UNIMPLEMENTED();
    return 1;
}

extern "C" void
XLib::XmbSetWMProperties(Display* display, Window w,
	const char* window_name, const char* icon_name, char** argv, int argc,
    XSizeHints* normal_hints, XWMHints* wm_hints, XClassHint* class_hints)
{
    UNIMPLEMENTED();
}

extern "C" Bool
XLib::XQueryPointer(Display *display, Window w, Window* root_return,
    Window* child_return, int* root_x_return, int* root_y_return,
    int* win_x_return, int *win_y_return,
    unsigned int* mask_return)
{
    UNIMPLEMENTED();
    return False;
}

extern "C" int
XLib::XDefineCursor(Display *display, Window w, Cursor cursor)
{
    UNIMPLEMENTED();
    return Success;
}

extern "C" Window
XLib::XGetSelectionOwner(Display* display, Atom selection)
{
    UNIMPLEMENTED();
    return None;
}

extern "C" Bool
XLib::XIfEvent(Display* display, XEvent* event_return,
    Bool (*predicate)(Display*, XEvent*, XPointer), XPointer arg)
{
    UNIMPLEMENTED();
    return Success;
}

extern "C" Status
XLib::XFreeColormap(Display* display, Colormap colormap)
{
    return Success;
}

extern "C" int
XLib::XSetSelectionOwner(Display* display, Atom selection, Window owner, XLib::Time time)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

extern "C" int
XLib::XmbTextListToTextProperty(Display* display, char** list, int count, XICCEncodingStyle style,
    XTextProperty* text_prop_return)
{
    UNIMPLEMENTED();
    return 0;
}

extern "C" Status
XLib::XmbTextPropertyToTextList(Display* display, const XTextProperty* text_prop,
    char*** list_return, int* count_return)
{
    UNIMPLEMENTED();
    return BadAlloc;
}

extern "C" Atom*
XLib::XListProperties(Display* dpy, Window w,
    int* num_prop_return)
{
    UNIMPLEMENTED();
    *num_prop_return = 0;
    return NULL;
}
}
#pragma GCC diagnostic pop
