#pragma once

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
}
}

void _x_extensions_close(XLib::Display *dpy);