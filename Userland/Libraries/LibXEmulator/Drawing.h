#pragma once

#include <LibGfx/Rect.h>

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
}
}

static inline XLib::XRectangle
make_xrect(int x, int y, int w, int h)
{
    XLib::XRectangle r;
    r.x = x;
    r.y = y;
    r.width = w;
    r.height = h;
    return r;
}

static inline XLib::XRectangle
xrect_from_intrect(const Gfx::IntRect& rect)
{
    return make_xrect(rect.left(), rect.top(),
        rect.width(), rect.height());
}

static inline Gfx::IntRect
intrect_from_xrect(const XLib::XRectangle& xrect)
{
    return Gfx::IntRect(xrect.x, xrect.y,
        xrect.width, xrect.height);
}