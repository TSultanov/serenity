#pragma once

#include <cstring>

namespace XLib {
extern "C" {
#include <X11/Xutil.h>
}
}

static inline XLib::XTextProperty
make_text_property(XLib::Atom type, int format, void* data, int length = -1, bool copy = false)
{
    XLib::XTextProperty ret;
    ret.encoding = type;
    ret.format = format;
    ret.value = copy ? (unsigned char*)strdup((const char*)data) : (unsigned char*)data;
    ret.nitems = length < 0 ? (ret.value ? strlen((const char*)ret.value) : 0) : length;
    return ret;
}

void _x_handle_send_root(XLib::Display* dpy, const XLib::XEvent& event);
