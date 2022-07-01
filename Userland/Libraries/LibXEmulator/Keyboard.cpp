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
XLib::XKeysymToKeycode(Display* display, KeySym keysym)
{
    UNIMPLEMENTED();
    return (KeyCode)0;
}

extern "C" int
XLib::XLookupString(XKeyEvent* key_event, char* buffer_return, int bytes_buffer,
    KeySym* keysym_return, XComposeStatus* status_in_out)
{
    UNIMPLEMENTED();
    return 0;
}

extern "C" KeySym
XLib::XkbKeycodeToKeysym(Display* dpy, unsigned int kc, int group, int level)
{
    UNIMPLEMENTED();
    return 0;
}

extern "C" Bool
XLib::XkbLookupKeySym(Display* dpy, KeyCode keycode,
    unsigned int modifiers, unsigned int* modifiers_return, KeySym* keysym_return)
{
    UNIMPLEMENTED();
    return (*keysym_return != NoSymbol);
}

extern "C" unsigned int
XLib::XkbKeysymToModifiers(Display* dpy, KeySym ks)
{
    switch (ks) {
    case XK_Shift_L:
    case XK_Shift_R:
        return ShiftMask;

    case XK_Caps_Lock:
        return LockMask;

    case XK_Control_L:
    case XK_Control_R:
        return ControlMask;

    case XK_Alt_L:
        return Mod1Mask;
    case XK_Alt_R:
        return Mod4Mask;

    case XK_Num_Lock:
        return Mod2Mask;

    case XK_Scroll_Lock:
        return Mod3Mask;
    }
    return 0;
}

extern "C" XModifierKeymap*
XLib::XGetModifierMapping(Display* display)
{
    XModifierKeymap* map = (XModifierKeymap*)calloc(sizeof(XModifierKeymap), 1);
    UNIMPLEMENTED();
    return map;
}

extern "C" int
XLib::XFreeModifiermap(XModifierKeymap *modmap)
{
    free(modmap->modifiermap);
    free(modmap);
    return Success;
}

extern "C" XkbDescPtr
XLib::XkbGetMap(Display* display, unsigned int which, unsigned int device_spec)
{
    XkbDescPtr desc = (XkbDescPtr)calloc(sizeof(XkbDescRec), 1);
    desc->device_spec = device_spec;
    if (XkbGetUpdatedMap(display, which, desc) != Success) {
        XkbFreeKeyboard(desc, 0, True);
        return NULL;
    }
    return desc;
}

extern "C" Status
XLib::XkbGetUpdatedMap(Display* display, unsigned int which, XkbDescPtr xkb)
{
    xkb->min_key_code = 1;
    xkb->max_key_code = 0;
    // We do not actually fill anything in here, but leave it all zeros.
    return Success;
}

extern "C" Status
XLib::XkbGetNames(Display* dpy, unsigned int which, XkbDescPtr xkb)
{
    // We do not actually fill anything in here, but leave it all zeros.
    return Success;
}

extern "C" void
XLib::XkbFreeKeyboard(XkbDescPtr xkb, unsigned int which, Bool freeDesc)
{
    if (!xkb)
        return;
    // We never actually fill in any of the structures.
    if (freeDesc)
        free(xkb);
}

extern "C" KeySym
XLib::XStringToKeysym(const char* string)
{
    UNIMPLEMENTED();
    return NoSymbol;
}

extern "C" char*
XLib::XKeysymToString(KeySym keysym)
{
    UNIMPLEMENTED();
    return NULL;
}

// #pragma mark - minor functions

extern "C" Bool
XLib::XkbTranslateKeyCode(XkbDescPtr xkb, KeyCode key, unsigned int mods,
    unsigned int* mods_rtrn, KeySym* keysym_rtrn)
{
    return XkbLookupKeySym(NULL, key, mods, mods_rtrn, keysym_rtrn);
}

extern "C" KeySym
XLib::XKeycodeToKeysym(Display* dpy, unsigned int kc, int index)
{
    return XkbKeycodeToKeysym(dpy, kc, 0, 0);
}

extern "C" KeySym
XLib::XLookupKeysym(XKeyEvent* key_event, int index)
{
    return XkbKeycodeToKeysym(key_event->display, key_event->keycode, 0, 0);
}

extern "C" Display*
XLib::XkbOpenDisplay(char *display_name, int *event_rtrn, int *error_rtrn,
    int *major_in_out, int *minor_in_out, int *reason_rtrn)
{
    return XOpenDisplay(display_name);
}

extern "C" Bool
XLib::XkbLibraryVersion(int *lib_major_in_out, int *lib_minor_in_out)
{
    return True;
}

extern "C" Bool
XLib::XkbQueryExtension(Display *dpy, int *opcode_rtrn, int *event_rtrn,
    int *error_rtrn, int *major_in_out, int *minor_in_out)
{
    return True;
}

// #pragma mark - stubs

extern "C" Bool
XLib::XkbUseExtension(Display* dpy, int* major_rtrn, int* minor_rtrn)
{
    UNIMPLEMENTED();
    return 0;
}

extern "C" int
XLib::XkbTranslateKeySym(Display* dpy, KeySym* sym_return, unsigned int modifiers, char* buffer, int nbytes, int* extra_rtrn)
{
    UNIMPLEMENTED();
    return 0;
}

extern "C" void
XLib::XConvertCase(KeySym keysym, KeySym *lower_return, KeySym *upper_return)
{
    UNIMPLEMENTED();
}

extern "C" KeySym*
XLib::XGetKeyboardMapping(Display *display, unsigned int first_keycode, int keycode_count, int *keysyms_per_keycode_return)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" int
XLib::XGetKeyboardControl(Display* dpy, XKeyboardState* state_return)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

extern "C" int
XLib::XChangeKeyboardControl(Display* dpy, unsigned long value_mask, XKeyboardControl* control)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

extern "C" int
XLib::XQueryKeymap(Display* dpy, char keys_return[32])
{
    UNIMPLEMENTED();
    return BadImplementation;
}

extern "C" Bool
XLib::XkbSelectEvents(Display *display, unsigned int device_spec,
    unsigned int bits_to_change, unsigned int values_for_bits)
{
    UNIMPLEMENTED();
    return False;
}

extern "C" Bool
XLib::XkbSelectEventDetails(Display* display, unsigned int device_spec, unsigned int event_type,
    unsigned long int bits_to_change, unsigned long int values_for_bits)
{
    UNIMPLEMENTED();
    return False;
}

extern "C" Status
XLib::XkbGetState(Display* dpy, unsigned int deviceSpec, XkbStatePtr rtrnState)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

extern "C" XkbDescPtr
XLib::XkbGetKeyboard(Display* display, unsigned int which, unsigned int device_spec)
{
    UNIMPLEMENTED();
    return NULL;
}

extern "C" Bool
XLib::XkbGetNamedIndicator(Display* dpy, Atom name,
    int* index_return, Bool* state_return, XkbIndicatorMapPtr map_return, Bool* real_return)
{
    UNIMPLEMENTED();
    return False;
}

extern "C" Bool
XLib::XkbSetNamedIndicator(Display* dpy, Atom name,
    Bool change_state, Bool state, Bool create_new, XkbIndicatorMapPtr map)
{
    UNIMPLEMENTED();
    return False;
}

extern "C" Bool
XLib::XkbBell(Display* display, Window window, int percent, Atom name)
{
    UNIMPLEMENTED();
    return False;
}

extern "C" Bool
XLib::XkbSetDetectableAutoRepeat(Display* display, Bool detectable, Bool* supported_rtrn)
{
    UNIMPLEMENTED();
    return False;
}

extern "C" Status
XLib::XkbGetControls(Display* display, unsigned long which, XkbDescPtr xkb)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

extern "C" int
XLib::XGrabKey(Display *display, int keycode, unsigned int modifiers, Window grab_window,
    Bool owner_events, int pointer_mode, int keyboard_mode)
{
    UNIMPLEMENTED();
    // TODO?
    return BadImplementation;
}

extern "C" int
XLib::XUngrabKey(Display *display, int keycode, unsigned int modifiers, Window grab_window)
{
    UNIMPLEMENTED();
    return Success;
}

extern "C" int
XLib::XGrabKeyboard(Display *display, Window grab_window, Bool owner_events,
    int pointer_mode, int keyboard_mode, XLib::Time time)
{
    UNIMPLEMENTED();
    // Pretend this worked.
    return GrabSuccess;
}

extern "C" int
XLib::XUngrabKeyboard(Display *display, XLib::Time time)
{
    UNIMPLEMENTED();
    return Success;
}

#pragma GCC diagnostic pop
