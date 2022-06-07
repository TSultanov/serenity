#include "Drawing.h"
#include "Undef.h"
#include "XWindow.h"
#include "ObjectManager.h"

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
#define Bool int
#include <X11/Xlibint.h>
}
}

using namespace XLib;

extern "C" int
XFillRectangle(Display *display, Drawable win, GC gc,
    int x, int y, unsigned int w, unsigned int h)
{
    XRectangle rect;
    rect.x = x;
    rect.y = y;
    rect.width = w;
    rect.height = h;
    return XFillRectangles(display, win, gc, &rect, 1);
}

extern "C" int
XFillRectangles(Display */*display*/, Drawable w, GC /*gc*/,
    XRectangle *rect, int n)
{
    auto window = ObjectManager::the().get_window(w); // FIXME: Consider implementing XWindow as a subclass of XDrawable
    auto& painter = window->painter();
    //bex_check_gc(window, gc);
    for (int i = 0; i < n; i++) {
        painter.fill_rect(intrect_from_xrect(rect[i]), Color::from_rgb(0));
    }
    return 0;
}