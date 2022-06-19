#include "XPixmap.h"
#include "ObjectManager.h"

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

extern "C" int
XLib::XFreePixmap(Display */*display*/, Pixmap pxm)
{
    auto pixmap = ObjectManager::the().get_pixmap(pxm);
    if (pixmap.is_null())
        return BadPixmap;
    ObjectManager::the().remove_pixmap(pxm);
    return Success;
}
