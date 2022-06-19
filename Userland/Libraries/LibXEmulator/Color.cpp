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

extern "C" Status
XLib::XQueryColors(Display */*display*/, Colormap /*colormap*/,
    XColor *defs_in_out, int ncolors)
{
    for (int i = 0; i < ncolors; i++) {
        Gfx::Color color = _x_pixel_to_rgb(defs_in_out[i].pixel);
        defs_in_out[i].red = color.red();
        defs_in_out[i].green = color.green();
        defs_in_out[i].blue = color.blue();
        defs_in_out[i].flags = DoRed | DoGreen | DoBlue;
        defs_in_out[i].pad = 0;
    }
    return Success;
}