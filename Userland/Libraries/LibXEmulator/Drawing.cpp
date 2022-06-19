#include "Drawing.h"
#include "Undef.h"
#include "XWindow.h"
#include "ObjectManager.h"
#include <LibGfx/ImageDecoder.h>

namespace XLib {
extern "C" {
#define register
#include <X11/Xlib.h>
#define Bool int
#include <X11/Xlibint.h>
#undef register
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

extern "C" int
XLib::XPutImage(Display */*display*/, Drawable d, GC /*gc*/, XImage* image,
    int /*src_x*/, int /*src_y*/, int dest_x, int dest_y,
    unsigned int width, unsigned int height)
{
    auto drawable = ObjectManager::the().get_drawable(d);
    if (drawable.is_null())
        return BadDrawable;

    //const auto srcRect = intrect_from_xrect(make_xrect(src_x, src_y, width, height));

    AK::Span<const u8> span(image->data, image->height*image->bytes_per_line);
    auto decoder = Gfx::ImageDecoder::try_create(span);
    auto frame = MUST(decoder->frame(0));
    auto bitmap = frame.image;

    //bex_check_gc(drawable, gc);

    drawable->painter().draw_tiled_bitmap(intrect_from_xrect(make_xrect(dest_x, dest_y, width, height)), *bitmap);
    return Success;
}

extern "C" void
XLib::Xutf8DrawString(Display */*display*/, Drawable w, XFontSet /*set*/, GC gc, int x, int y, const char* str, int /*len*/)
{
    // FIXME: Use provided fonts!
    auto window = ObjectManager::the().get_window(w); // FIXME: Consider implementing XWindow as a subclass of XDrawable
    auto& painter = window->painter();
    //bex_check_gc(window, gc);
    Gfx::IntRect rect(x, y, window->widget()->width()-x, window->widget()->height()-y);
    painter.draw_text(rect, str, Gfx::TextAlignment::TopLeft, Color::from_rgb(gc->values.foreground), Gfx::TextElision::None, Gfx::TextWrapping::DontWrap);
}

extern "C" int
XLib::XDrawString(Display* display, Drawable w, GC gc, int x, int y, const char* str, int len)
{
    Xutf8DrawString(display, w, NULL, gc, x, y, str, len);
    return 0;
}

extern "C" int
XLib::XCopyArea(Display* /*display*/, Drawable src, Drawable dest, GC /*gc*/,
    int src_x, int src_y, unsigned int width, unsigned int height, int dest_x, int dest_y)
{
    auto src_d = ObjectManager::the().get_drawable(src);
    auto dest_d = ObjectManager::the().get_drawable(dest);
    if (src_d.is_null() || dest_d.is_null())
        return BadDrawable;

    const Gfx::IntRect src_rect(src_x, src_y, width, height);
    const Gfx::IntRect dest_rect(dest_x, dest_y, width, height);


    auto cropped_bitmap = MUST(src_d->bitmap()->cropped(src_rect));
    dest_d->painter().draw_tiled_bitmap(dest_rect, cropped_bitmap);
    return Success;
}