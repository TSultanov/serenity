#include "Color.h"

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
}
}

static XLib::XID sDummy;

extern "C" XLib::Colormap
XLib::XCreateColormap(XLib::Display*, XLib::Window, XLib::Visual* visual, int allocate)
{
    // Return a dummy colormap for TrueColor, so things do not complain.
    if (allocate == AllocNone && ((visual && visual->c_class == TrueColor) || !visual))
        return (XLib::Colormap)&sDummy;
    return None;
}

extern "C" int
XLib::XAllocColor(Display* /*dpy*/, Colormap /*cmap*/, XColor* def)
{
    def->pixel = _x_rgb_to_pixel(Gfx::Color(def->red, def->green, def->blue));
    return 1;
}