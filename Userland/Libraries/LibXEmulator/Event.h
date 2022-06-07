#pragma once

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
}
}

#define _x_current_time() (Time(system_time() / 1000))

void _x_init_events(XLib::Display* dpy);
void _x_finalize_events(XLib::Display* dpy);

void _x_put_event(XLib::Display* dpy, const XLib::XEvent& event);
