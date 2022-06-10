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

extern "C" int
XLib::XFillRectangle(Display *display, Drawable win, GC gc,
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
XLib::XFillRectangles(Display */*display*/, Drawable w, GC gc,
    XRectangle *rect, int n)
{
    auto window = ObjectManager::the().get_window(w); // FIXME: Consider implementing XWindow as a subclass of XDrawable
    auto& painter = window->painter();
    //bex_check_gc(window, gc);
    for (int i = 0; i < n; i++) {
        painter.fill_rect(intrect_from_xrect(rect[i]), Color::from_rgb(gc->values.foreground));
        dbgln("background color: {}", gc->values.foreground);
    }
    return 0;
}

extern "C" void
XLib::Xutf8DrawString(Display */*display*/, Drawable w, XFontSet /*set*/, GC gc, int x, int y, const char* str, int /*len*/)
{
    // FIXME: Use provided fonts!
    auto window = ObjectManager::the().get_window(w); // FIXME: Consider implementing XWindow as a subclass of XDrawable
    auto& painter = window->painter();
    //bex_check_gc(window, gc);
    Gfx::IntRect rect(x, y, window->width()-x, window->height()-y);
    painter.draw_text(rect, str, Gfx::TextAlignment::TopLeft, Color::from_rgb(gc->values.foreground), Gfx::TextElision::None, Gfx::TextWrapping::DontWrap);
}

extern "C" int
XLib::XDrawString(Display* display, Drawable w, GC gc, int x, int y, const char* str, int len)
{
    Xutf8DrawString(display, w, NULL, gc, x, y, str, len);
    return 0;
}