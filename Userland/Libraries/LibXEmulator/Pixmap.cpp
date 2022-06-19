#include "XPixmap.h"

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
}
}

extern "C" XLib::Pixmap
XLib::XCreatePixmap(Display* display, Drawable /*d*/,
    unsigned int width, unsigned int height, unsigned int /*depth*/)
{
    Gfx::IntRect rect(0, 0, width, height);
    auto pixmap = MUST(XPixmap::try_create(display, rect));
    return pixmap->id();
}