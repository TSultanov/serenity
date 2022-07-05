#include <AK/Format.h>
#include "ObjectManager.h"
#include "Property.h"
#include "Atom.h"
#include "Event.h"
namespace XLib {
extern "C" {
#define register
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#include <X11/Xutil.h>
#undef register
}
}

using namespace XLib;

/* The _MOTIF_WM_HINTS property is widely used but not very well documented.
 * Most producers and consumers of this API seem to copy and paste the definitions
 * from Motif's headers, but the precise semantics are not very well defined. */
enum {
	MWM_HINTS_FUNCTIONS		= (1L << 0),
	MWM_HINTS_DECORATIONS	= (1L << 1),
	MWM_HINTS_INPUT_MODE	= (1L << 2),
	MWM_HINTS_STATUS		= (1L << 3),
};
enum {
	MWM_FUNC_ALL			= (1L << 0),
	MWM_FUNC_RESIZE			= (1L << 1),
	MWM_FUNC_MOVE			= (1L << 2),
	MWM_FUNC_MINIMIZE		= (1L << 3),
	MWM_FUNC_MAXIMIZE		= (1L << 4),
	MWM_FUNC_CLOSE			= (1L << 5),
};
enum {
	MWM_DECOR_ALL			= (1L << 0),
	MWM_DECOR_BORDER		= (1L << 1),
	MWM_DECOR_RESIZEH		= (1L << 2),
	MWM_DECOR_TITLE			= (1L << 3),
	MWM_DECOR_MENU			= (1L << 4),
	MWM_DECOR_MINIMIZE		= (1L << 5),
	MWM_DECOR_MAXIMIZE		= (1L << 6),
};
enum {
	MWM_INPUT_MODELESS = 0,
	MWM_INPUT_PRIMARY_APPLICATION_MODAL = 1,
	MWM_INPUT_SYSTEM_MODAL = 2,
	MWM_INPUT_FULL_APPLICATION_MODAL = 3,
};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-nonliteral"
static void
unknown_property(const char* format, Atom atom1, Atom atom2 = None)
{
	char* value1 = XGetAtomName(NULL, atom1);
	char* value2 = atom2 != None ? XGetAtomName(NULL, atom2) : NULL;
	if (value2)
		fprintf(stderr, format, value1, value2);
	else
		fprintf(stderr, format, value1);
	free(value1);
	free(value2);
}
#pragma clang diagnostic pop

static void
_x_property_notify(XWindow* window, Atom property, int state)
{
    if (!window || !(window->event_mask() & PropertyChangeMask))
        return;

    XEvent event = {};
    event.type = PropertyNotify;
    event.xproperty.window = window->id();
    event.xproperty.time = _x_current_time();
    event.xproperty.atom = property;
    event.xproperty.state = state;
    _x_put_event(window->display(), event);
}


void
_x_handle_send_root(XLib::Display* dpy, const XLib::XEvent& event)
{
    if (event.type != ClientMessage) {
        dbgln("libX11: unhandled sent root event, type {}", event.type);
        return;
    }

    switch (event.xclient.message_type) {
    case Atoms::_NET_WM_STATE: {
        auto window = ObjectManager::the().get_window(event.xclient.window);
        if (!window || !window->parent_window())
            return;

        enum {
            _NET_WM_STATE_REMOVE = 0,
            _NET_WM_STATE_ADD = 1,
            _NET_WM_STATE_TOGGLE = 2,
        };
        const int32_t action = event.xclient.data.l[0];

        for (int i = 1; i < 3; i++) {
            XLib::Atom value = event.xclient.data.l[i];
            if (value == None)
                continue;

            if (action == _NET_WM_STATE_ADD) {
                XChangeProperty(dpy, event.xclient.window, Atoms::_NET_WM_STATE, XA_ATOM, -1,
                    PropModeAppend, (unsigned char*)&value, 1);
            } else {
                // FIXME: This is not correct at all!
                XDeleteProperty(dpy, event.xclient.window, Atoms::_NET_WM_STATE);
            }
        }
        break;
    }

    default:
        dbgln("libX11: unhandled sent root message: {}", event.xclient.message_type);
        break;
    }
}


extern "C" int
XLib::XChangeProperty(Display* /*dpy*/, Window w, Atom property, Atom type,
    int /*format*/, int /*mode*/, const unsigned char* data, int nelements)
{
    // TODO: mode?

    //auto *non_const_data = const_cast<unsigned char*>(data);

    switch (property) {
//    case Atoms::WM_PROTOCOLS:
//        return XSetWMProtocols(dpy, w, reinterpret_cast<Atom*>(non_const_data), nelements);

//    case XA_WM_NAME:
//    case Atoms::WM_NAME:
//    case Atoms::_NET_WM_NAME: {
//        XTextProperty tp = make_text_property(type, format, non_const_data, nelements);
//        XSetWMName(dpy, w, &tp);
//        return Success;
//    }
//    case XA_WM_ICON_NAME:
//    case Atoms::WM_ICON_NAME:
//    case Atoms::_NET_WM_ICON_NAME: {
//        XTextProperty tp = make_text_property(type, format, non_const_data, nelements);
//        XSetWMIconName(dpy, w, &tp);
//        return Success;
//    }

//    case Atoms::_MOTIF_WM_HINTS: {
//        if (type != Atoms::_MOTIF_WM_HINTS || nelements < 1)
//            return BadValue;
//
//        auto window = ObjectManager::the().get_window(w);
//        if (!window || !window->widget()->window())
//            return BadWindow;
//        auto bwindow = window->widget()->window();
//
//		const long flags = values[0];
//        if (flags & MWM_HINTS_FUNCTIONS) {
//            long func = values[1];
//            if (func & MWM_FUNC_ALL)
//                func = ~0L;
//
//            int32 bflags = 0;
//            if (!(func & MWM_FUNC_RESIZE))
//                bflags |= B_NOT_RESIZABLE;
//            if (!(func & MWM_FUNC_MOVE))
//                bflags |= B_NOT_MOVABLE;
//            if (!(func & MWM_FUNC_MINIMIZE))
//                bflags |= B_NOT_MINIMIZABLE;
//            if (!(func & MWM_FUNC_MAXIMIZE))
//                bflags |= B_NOT_ZOOMABLE;
//            if (!(func & MWM_FUNC_CLOSE))
//                bflags |= B_NOT_CLOSABLE;
//
//            int32 setflags = bwindow->Flags();
//            setflags &= ~(B_NOT_RESIZABLE | B_NOT_MOVABLE | B_NOT_MINIMIZABLE
//                | B_NOT_ZOOMABLE | B_NOT_CLOSABLE);
//            setflags |= bflags;
//            bwindow->SetFlags(setflags);
//        }
//        if (flags & MWM_HINTS_DECORATIONS) {
//            long decor = values[2];
//            if (decor & MWM_DECOR_ALL)
//                decor = ~0L;
//
//            // We ignore most of these and rely instead on MWM_HINTS_FUNCTIONS.
//            bwindow->SetLook((decor & MWM_DECOR_TITLE) ? B_TITLED_WINDOW_LOOK :
//                    (decor & MWM_DECOR_BORDER) ? B_BORDERED_WINDOW_LOOK : B_NO_BORDER_WINDOW_LOOK);
//        }
//        if ((flags & MWM_HINTS_INPUT_MODE) && !window->override_redirect) {
//            long input = values[3];
//            switch (input) {
//            case MWM_INPUT_MODELESS:
//                bwindow->SetFeel(B_NORMAL_WINDOW_FEEL);
//                break;
//
//            case MWM_INPUT_PRIMARY_APPLICATION_MODAL:
//            case MWM_INPUT_FULL_APPLICATION_MODAL:
//                bwindow->SetFeel(B_MODAL_APP_WINDOW_FEEL);
//                break;
//
//            case MWM_INPUT_SYSTEM_MODAL:
//                bwindow->SetFeel(B_MODAL_ALL_WINDOW_FEEL);
//                break;
//            }
//        }
//        if (flags & MWM_HINTS_STATUS) {
//            // TODO: What is this for?
//        }
//
//        return Success;
//    }
//    case Atoms::_NET_WM_WINDOW_TYPE: {
//        if (type != XA_ATOM || nelements != 1)
//            return BadValue;
//        XWindow* window = Drawables::get_window(w);
//        if (!window || !window->bwindow)
//            return BadWindow;
//        BWindow* bwindow = window->bwindow;
//
//        switch (*(Atom*)data) {
//        case Atoms::_NET_WM_WINDOW_TYPE_DROPDOWN_MENU:
//        case Atoms::_NET_WM_WINDOW_TYPE_POPUP_MENU:
//        case Atoms::_NET_WM_WINDOW_TYPE_TOOLTIP:
//            bwindow->SetLook(B_NO_BORDER_WINDOW_LOOK);
//            if (!window->override_redirect) {
//                bwindow->SetFeel(B_FLOATING_APP_WINDOW_FEEL);
//                bwindow->SetFlags(bwindow->Flags() | B_AVOID_FOCUS);
//            }
//            break;
//
//        default:
//            unknown_property("libX11: unhandled _NET_WM_WINDOW_TYPE: %s\n", *(Atom*)data);
//            // fall through
//        case Atoms::_NET_WM_WINDOW_TYPE_NORMAL:
//            bwindow->SetLook(B_TITLED_WINDOW_LOOK);
//            if (!window->override_redirect) {
//                bwindow->SetFeel(B_NORMAL_WINDOW_FEEL);
//                bwindow->SetFlags(bwindow->Flags() & ~B_AVOID_FOCUS);
//            }
//            break;
//        }
//
//        return Success;
//    }
//    case Atoms::_NET_WM_STATE: {
//        if (type != XA_ATOM || nelements < 1)
//            return BadValue;
//
//        XWindow* window = Drawables::get_window(w);
//        if (!window || !window->bwindow)
//            return BadWindow;
//
//        Atom* values = (Atom*)data;
//        for (int i = 0; i < nelements; i++) {
//            switch (values[i]) {
//            case Atoms::_NET_WM_STATE_MODAL:
//                window->bwindow->SetFeel(window->transient_for ?
//                                                               B_MODAL_SUBSET_WINDOW_FEEL : B_MODAL_APP_WINDOW_FEEL);
//                window->bwindow->Activate();
//                break;
//
//            default:
//                unknown_property("libX11: unhandled _NET_WM_STATE: %s\n", values[i]);
//                break;
//            }
//        }
//
//        // Adding a window to a subset only works if it has a SUBSET feel.
//        // So we add it (again) after changing feels.
//        if (XWindow* transient_for = Drawables::get_window(window->transient_for))
//            transient_for->bwindow->AddToSubset(window->bwindow);
//
//        return Success;
//    }
//
//    case Atoms::CLIPBOARD:
//        return _x_handle_set_clipboard(dpy, w, type, data, nelements);

    case Atoms::_NET_WM_USER_TIME:
    case Atoms::_NET_WM_USER_TIME_WINDOW:
        // We don't care about these.
        break;

    default: {
        if (type == XA_ATOM && nelements)
            dbgln("libX11: unhandled Property: {} = {}", property, *reinterpret_cast<const Atom*>(data));
        else
            dbgln("libX11: unhandled Property: {}<{}>\n", property, type);

        // Send a property-change event anyway.
        // (Some applications set a bogus property to get the time field from the reply event.)
        _x_property_notify(ObjectManager::the().get_window(w), property, PropertyDelete);
        break;
    }
    }
    return BadImplementation;
}

extern "C" int
XLib::XDeleteProperty(Display* /*display*/, Window /*w*/, Atom property)
{
    dbgln("libX11: unhandled Property (delete): {}", property);
    return BadImplementation;
}

extern "C" int
XLib::XGetWindowProperty(Display* /*dpy*/, Window w, Atom property,
    long /*long_offset*/, long /*long_length*/, Bool /*del*/, Atom req_type,
    Atom* actual_type_return, int* actual_format_return,
    unsigned long* nitems_return, unsigned long* bytes_after_return, unsigned char** prop_return)
{
    // Always initialize return values, same as the real Xlib.
    *actual_type_return = 0;
    *actual_format_return = 0;
    *nitems_return = 0;
    *bytes_after_return = 0;
    *prop_return = NULL;
    
    switch(property) {
    case Atoms::_MOTIF_WM_HINTS: {
        RefPtr<XWindow> window = ObjectManager::the().get_window(w);
        if (window.is_null() || !(window->host_window()))
            return BadWindow;
        auto bwindow = window->host_window();

        long* values = (long*)calloc(sizeof(long), 4);
        values[0] = MWM_HINTS_FUNCTIONS | MWM_HINTS_DECORATIONS | MWM_HINTS_INPUT_MODE;
        long func = 0; {
            if (bwindow->is_resizable())
                func |= MWM_FUNC_RESIZE;
//            if (bwindow->is_movable())
            func |= MWM_FUNC_MOVE;
            if (bwindow->is_minimizable())
                func |= MWM_FUNC_MINIMIZE;
//            if (bwindow->is_maximizable())
            func |= MWM_FUNC_MAXIMIZE;
            if (bwindow->is_closeable())
                func |= MWM_FUNC_CLOSE;
        }
        values[1] = func;
        long decor = MWM_DECOR_TITLE | MWM_DECOR_BORDER;
        values[2] = decor;
        long input = 0;
        if(bwindow->is_modal())
        {
            input = MWM_INPUT_PRIMARY_APPLICATION_MODAL;
        }
        else
        {
            input = MWM_INPUT_MODELESS;

        }
        values[3] = input;

        *actual_type_return = Atoms::_MOTIF_WM_HINTS;
        *actual_format_return = 32;
        *prop_return = (unsigned char*)values;
        *nitems_return = 4;
        return Success;
    }

    case Atoms::_NET_SUPPORTING_WM_CHECK:
        // Only needed so client applications can detect when the WM changes.
        // That never happens for us, so we can ignore this.
        return BadImplementation;
    }

    unknown_property("libX11: unhandled Property (get): %s<%s>\n", property, req_type);
        return BadImplementation;
}