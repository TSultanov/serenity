#pragma once

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
}
}

#include <time.h>

inline XLib::Time _x_current_time()
{
    return XLib::Time(time(nullptr) / 1000);
}

void _x_init_events(XLib::Display* dpy);
void _x_finalize_events(XLib::Display* dpy);

void _x_put_event(XLib::Display* dpy, const XLib::XEvent& event);
