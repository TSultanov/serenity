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

extern "C" int
XLookupString(XKeyEvent* key_event, char* buffer_return, int bytes_buffer,
    KeySym* keysym_return, XComposeStatus* status_in_out)
{
    UNIMPLEMENTED();
    return 0;
}

extern "C" KeySym
XkbKeycodeToKeysym(Display* dpy, unsigned int kc, int group, int level)
{
    UNIMPLEMENTED();
    return 0;
}

extern "C" Bool
XkbLookupKeySym(Display* dpy, KeyCode keycode,
    unsigned int modifiers, unsigned int* modifiers_return, KeySym* keysym_return)
{
    UNIMPLEMENTED();
    return (*keysym_return != NoSymbol);
}

extern "C" unsigned int
XkbKeysymToModifiers(Display* dpy, KeySym ks)
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
XGetModifierMapping(Display* display)
{
    XModifierKeymap* map = (XModifierKeymap*)calloc(sizeof(XModifierKeymap), 1);
    UNIMPLEMENTED();
    return map;
}

extern "C" int
XFreeModifiermap(XModifierKeymap *modmap)
{
    free(modmap->modifiermap);
    free(modmap);
    return Success;
}

extern "C" XkbDescPtr
XkbGetMap(Display* display, unsigned int which, unsigned int device_spec)
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
XkbGetUpdatedMap(Display* display, unsigned int which, XkbDescPtr xkb)
{
    xkb->min_key_code = 1;
    xkb->max_key_code = 0;
    // We do not actually fill anything in here, but leave it all zeros.
    return Success;
}

extern "C" Status
XkbGetNames(Display* dpy, unsigned int which, XkbDescPtr xkb)
{
    // We do not actually fill anything in here, but leave it all zeros.
    return Success;
}

extern "C" void
XkbFreeKeyboard(XkbDescPtr xkb, unsigned int which, Bool freeDesc)
{
    if (!xkb)
        return;
    // We never actually fill in any of the structures.
    if (freeDesc)
        free(xkb);
}

extern "C" KeySym
XStringToKeysym(const char* string)
{
    UNIMPLEMENTED();
    return NoSymbol;
}

extern "C" char*
XKeysymToString(KeySym keysym)
{
    UNIMPLEMENTED();
    return NULL;
}

// #pragma mark - minor functions

extern "C" Bool
XkbTranslateKeyCode(XkbDescPtr xkb, KeyCode key, unsigned int mods,
    unsigned int* mods_rtrn, KeySym* keysym_rtrn)
{
    return XkbLookupKeySym(NULL, key, mods, mods_rtrn, keysym_rtrn);
}

extern "C" KeySym
XKeycodeToKeysym(Display* dpy, unsigned int kc, int index)
{
    return XkbKeycodeToKeysym(dpy, kc, 0, 0);
}

extern "C" KeySym
XLookupKeysym(XKeyEvent* key_event, int index)
{
    return XkbKeycodeToKeysym(key_event->display, key_event->keycode, 0, 0);
}

extern "C" Display*
XkbOpenDisplay(char *display_name, int *event_rtrn, int *error_rtrn,
    int *major_in_out, int *minor_in_out, int *reason_rtrn)
{
    return XOpenDisplay(display_name);
}

extern "C" Bool
XkbLibraryVersion(int *lib_major_in_out, int *lib_minor_in_out)
{
    return True;
}

extern "C" Bool
XkbQueryExtension(Display *dpy, int *opcode_rtrn, int *event_rtrn,
    int *error_rtrn, int *major_in_out, int *minor_in_out)
{
    return True;
}

// #pragma mark - stubs

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

#pragma GCC diagnostic pop
