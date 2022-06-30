#include <AK/Format.h>

namespace XLib {
extern "C" {
#define register
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/XKBlib.h>
#undef register
#include "tables/keysymlist.h"
}
}

#define UNIMPLEMENTED() dbgln("Stub: {}", __func__)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-result"

using namespace XLib;

extern "C" KeyCode
XKeysymToKeycode(Display* display, KeySym keysym)
{
    UNIMPLEMENTED();
    return 0;
}

extern "C" Bool
XkbUseExtension(Display* dpy, int* major_rtrn, int* minor_rtrn)
{
    UNIMPLEMENTED();
    return 0;
}

extern "C" int
XkbTranslateKeySym(Display* dpy, KeySym* sym_return, unsigned int modifiers, char* buffer, int nbytes, int* extra_rtrn)
{
    UNIMPLEMENTED();
    return 0;
}

extern "C" void
XConvertCase(KeySym keysym, KeySym *lower_return, KeySym *upper_return)
{
    UNIMPLEMENTED();
}

extern "C" KeySym*
XGetKeyboardMapping(Display *display, unsigned int first_keycode, int keycode_count, int *keysyms_per_keycode_return)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" int
XGetKeyboardControl(Display* dpy, XKeyboardState* state_return)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

extern "C" int
XChangeKeyboardControl(Display* dpy, unsigned long value_mask, XKeyboardControl* control)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

extern "C" int
XQueryKeymap(Display* dpy, char keys_return[32])
{
    UNIMPLEMENTED();
    return BadImplementation;
}

extern "C" Bool
XkbSelectEvents(Display *display, unsigned int device_spec,
    unsigned int bits_to_change, unsigned int values_for_bits)
{
    UNIMPLEMENTED();
    return False;
}

extern "C" Bool
XkbSelectEventDetails(Display* display, unsigned int device_spec, unsigned int event_type,
    unsigned long int bits_to_change, unsigned long int values_for_bits)
{
    UNIMPLEMENTED();
    return False;
}

extern "C" Status
XkbGetState(Display* dpy, unsigned int deviceSpec, XkbStatePtr rtrnState)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

extern "C" XkbDescPtr
XkbGetKeyboard(Display* display, unsigned int which, unsigned int device_spec)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" Bool
XkbGetNamedIndicator(Display* dpy, Atom name,
    int* index_return, Bool* state_return, XkbIndicatorMapPtr map_return, Bool* real_return)
{
    UNIMPLEMENTED();
    return False;
}

extern "C" Bool
XkbSetNamedIndicator(Display* dpy, Atom name,
    Bool change_state, Bool state, Bool create_new, XkbIndicatorMapPtr map)
{
    UNIMPLEMENTED();
    return False;
}

extern "C" Bool
XkbBell(Display* display, Window window, int percent, Atom name)
{
    UNIMPLEMENTED();
    return False;
}

extern "C" Bool
XkbSetDetectableAutoRepeat(Display* display, Bool detectable, Bool* supported_rtrn)
{
    UNIMPLEMENTED();
    return False;
}

extern "C" Status
XkbGetControls(Display* display, unsigned long which, XkbDescPtr xkb)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

extern "C" int
XGrabKey(Display *display, int keycode, unsigned int modifiers, Window grab_window,
    Bool owner_events, int pointer_mode, int keyboard_mode)
{
    UNIMPLEMENTED();
    // TODO?
    return BadImplementation;
}

extern "C" int
XUngrabKey(Display *display, int keycode, unsigned int modifiers, Window grab_window)
{
    UNIMPLEMENTED();
    return Success;
}

extern "C" int
XGrabKeyboard(Display *display, Window grab_window, Bool owner_events,
    int pointer_mode, int keyboard_mode, XLib::Time time)
{
    UNIMPLEMENTED();
    // Pretend this worked.
    return GrabSuccess;
}

extern "C" int
XUngrabKeyboard(Display *display, XLib::Time time)
{
    UNIMPLEMENTED();
    return Success;
}


extern "C" int
XLookupString(XKeyEvent* key_event, char* buffer_return, int bytes_buffer,
    KeySym* keysym_return, XComposeStatus* status_in_out)
{
    UNIMPLEMENTED();
    return 0;
}

#pragma GCC diagnostic pop
